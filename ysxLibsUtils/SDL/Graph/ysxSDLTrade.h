#pragma once

#ifndef YSXSDLTRADE_H
#define YSXSDLTRADE_H


// SDL STUFFS:
// Uncomment if you have that directory tree:
#ifdef USE_SDL3
#include "SDL3/SDL.h"
#endif
#ifdef USE_SDL2
#include "SDL2/SDL.h"
#endif


// #####################
// ####### By Sophia Cristina
// ####### SDL for graphs related to trading, this is not about financial market in general (accounting and etc).
// #####################

#include "../../../ysxMath/ysxMath.h"
#include "ysxSDLGraphs.h"
#include "../Text/ysxSDLText.h"

// #################################################
// REFERENCES:
//
// #################################################


// #################################################
// FUNCTIONS:
// #################################################

// #################################################
// CLASSES:
// #################################################

// Plot Candle graphs with indicators:
class ysxSDL_CandleGraphPlot
{
private:
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
    TTF_Font* Font = nullptr;

    uint16_t Width, Height;

public:
    // Draw candlesticks and indicator lines:
    void Plot(const std::vector<ysxTRADE_Candle>& Candles, const uint16_t WidthDivs, const uint16_t HeightDivs, const std::vector<std::vector<double>>& IndicatorsLines, const std::vector<Point3D<uint8_t>>& Colors, const std::vector<uint8_t> LineThickness)
    {
        if (!Renderer || Candles.empty()) { std::cerr << "Either 'std::vector' 'Candles' is empty or 'Renderer' creation failed!\n"; return; }

        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        SDL_RenderClear(Renderer);
        Font = TTF_OpenFont("Ac437_IBM_DOS_ISO9-2x.ttf", 8);
        if (!Font) { std::cerr << "Failed to load font: " << TTF_GetError() << '\n'; }

        // Determine price range for vertical scaling:
        double MinPrice = Candles.front().Low;
        double MaxPrice = Candles.front().High;
        uint16_t HigherCandle, LowerCandle;
        for (size_t n = 0; n < Candles.size(); ++n)
        {
            if (Candles[n].Low < MinPrice) { MinPrice = Candles[n].Low; LowerCandle = n; }
            if (Candles[n].High > MaxPrice) { MaxPrice = Candles[n].High; HigherCandle = n; }
        }

        double Range = MaxPrice - MinPrice;
        if (Range <= 0.0) { Range = 1.0; }

        size_t CandleCount = (size_t)Candles.size();
        double CandleWidth = (double)Width / CandleCount;


        // #######

        // Division lines:
        uint16_t HDiv = Height / HeightDivs, WDiv = Width / WidthDivs;
        std::string Text;
        SDL_SetRenderDrawColor(Renderer, 95, 95, 95, 255);
        SDL_Color WhiteColor = {255, 255, 255, 255};
        for (uint16_t n = 0; n < HDiv; ++n)
        {
            SDL_RenderDrawLine(Renderer, 0, HDiv * n, Width, HDiv * n);
            Text = std::to_string(MinPrice + (Range / HeightDivs) * n);
            SDL_Surface* TextSurface = TTF_RenderText_Blended(Font, Text.c_str(), WhiteColor);
            if (TextSurface)
            {
                SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
                SDL_Rect DestRect = {(short)(Width - 80), (short)(Height - n * HDiv - 15), (uint16_t)TextSurface->w, (uint16_t)TextSurface->h};
                SDL_RenderCopy(Renderer, TextTexture, nullptr, &DestRect);
                DestRect = {7, (short)(Height - n * HDiv - 15), (uint16_t)TextSurface->w, (uint16_t)TextSurface->h};
                SDL_RenderCopy(Renderer, TextTexture, nullptr, &DestRect);
                SDL_DestroyTexture(TextTexture);
                SDL_FreeSurface(TextSurface);
            }
            else { std::cerr << "No TextSurface\n"; }
        }
        for (uint16_t n = 0; n < WDiv; ++n)
        {
            SDL_RenderDrawLine(Renderer, WDiv * n, 0, WDiv * n, Height);
            Text = std::to_string(n * Candles.size() / WidthDivs);
            SDL_Surface* TextSurface = TTF_RenderText_Blended(Font, Text.c_str(), WhiteColor);
            if (TextSurface)
            {
                SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
                SDL_Rect DestRect = {(short)(n * WDiv + 7), (short)(Height - 10), (uint16_t)TextSurface->w, (uint16_t)TextSurface->h};
                SDL_RenderCopy(Renderer, TextTexture, nullptr, &DestRect);
                SDL_DestroyTexture(TextTexture);
                SDL_FreeSurface(TextSurface);
            }
            else { std::cerr << "No TextSurface\n"; }

        }


        // Draw candles:
        for (size_t i = 0; i < CandleCount; ++i)
        {
            ysxTRADE_Candle c = Candles[i];
            size_t x = (size_t)(i * CandleWidth + CandleWidth * 0.5);

            size_t yHigh = Height - (size_t)(((c.High - MinPrice) / Range) * Height);
            size_t yLow = Height - (size_t)(((c.Low - MinPrice) / Range) * Height);
            size_t yOpen = Height - (size_t)(((c.Open - MinPrice) / Range) * Height);
            size_t yClose = Height - (size_t)(((c.Close - MinPrice) / Range) * Height);

            // Wick:
            SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(Renderer, x, yHigh, x, yLow);

            bool Rising = (c.Close >= c.Open);
            Rising ? SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255) : SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);

            // Body:
            SDL_Rect Body;
            Body.x = (size_t)i * CandleWidth;
            Body.w = (size_t)CandleWidth;// * 0.7;
            Body.y = std::min(yOpen, yClose);
            Body.h = std::abs((int)yClose - (int)yOpen);
            if (Body.h < 1) { Body.h = 1; } // Avoid zero height
            SDL_RenderFillRect(Renderer, &Body);
        }


        // #######


        // Draw indicator lines:
        size_t Lines = IndicatorsLines.size();
        for (size_t n = 0; n < Lines; ++n)
        {
            SDL_Color TextClr;
            if (IndicatorsLines[n].size() < 2) { continue; }
            if (Colors.empty())
            {
                SDL_SetRenderDrawColor(Renderer, 255, 255, 0, 255);
                TextClr = {255, 255, 0, 255};
            }
            else
            {
                SDL_SetRenderDrawColor(Renderer, Colors[n % Lines].x, Colors[n % Lines].y, Colors[n % Lines].z, 255);
                TextClr = {Colors[n % Lines].x, Colors[n % Lines].y, Colors[n % Lines].z, 255};
            }

            Text = std::to_string(IndicatorsLines[n].back());
            SDL_Surface* TextSurface = TTF_RenderText_Blended(Font, Text.c_str(), TextClr);
            if (TextSurface)
            {
                SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
                SDL_Rect DestRect = {84, (short)(10 * n + 10), (uint16_t)TextSurface->w, (uint16_t)TextSurface->h};
                SDL_RenderCopy(Renderer, TextTexture, nullptr, &DestRect);
                SDL_DestroyTexture(TextTexture);
                SDL_FreeSurface(TextSurface);
            }
            else { std::cerr << "No TextSurface\n"; }

            size_t Offset = Candles.size() - IndicatorsLines[n].size();
            for (size_t m = 1; m < IndicatorsLines[n].size(); ++m)
            {
                double Val1 = IndicatorsLines[n][m - 1];
                double Val2 = IndicatorsLines[n][m];

                size_t x1 = (size_t)((Offset + m - 1) * CandleWidth + CandleWidth / 2.0);
                size_t x2 = (size_t)((Offset + m) * CandleWidth + CandleWidth / 2.0);
                size_t y1 = Height - (size_t)(((Val1 - MinPrice) / Range) * Height);
                size_t y2 = Height - (size_t)(((Val2 - MinPrice) / Range) * Height);

                SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
                if (!LineThickness.empty() && n < LineThickness.size())
                {
                    if (LineThickness[n] > 0)
                    {
                        for (size_t Thick = 1; Thick < LineThickness[n]; ++Thick)
                        {
                            if (y1 + Thick < Height && y2 + Thick < Height) { SDL_RenderDrawLine(Renderer, x1, y1 + Thick, x2, y2 + Thick); }
                            if (y1 - Thick > 0 && y2 - Thick > 0) { SDL_RenderDrawLine(Renderer, x1, y1 - Thick, x2, y2 - Thick); }
                        }
                    }
                }
            }
        }


        // Max / Min prices text:
        std::cout << "DRAW TEXT\n";
        Text = "LOWER CANDLE: Close: " + std::to_string(Candles[LowerCandle].Close) + " | Low: " + std::to_string(MinPrice);
        SDL_Surface* TextSurface = TTF_RenderText_Blended(Font, Text.c_str(), WhiteColor);
        SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
        SDL_Rect DestRect = {(short)(Width * 0.5), (short)(Height - 20), (uint16_t)TextSurface->w, (uint16_t)TextSurface->h};
        SDL_RenderCopy(Renderer, TextTexture, nullptr, &DestRect);
        SDL_DestroyTexture(TextTexture); SDL_FreeSurface(TextSurface);

        Text = "HIGHER CANDLE: Close: " + std::to_string(Candles[HigherCandle].Close) + " | High: " + std::to_string(MaxPrice);
        TextSurface = TTF_RenderText_Blended(Font, Text.c_str(), WhiteColor);
        TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
        DestRect = {(short)(Width * 0.5), (short)(Height - 30), (uint16_t)TextSurface->w, (uint16_t)TextSurface->h};
        SDL_RenderCopy(Renderer, TextTexture, nullptr, &DestRect);
        SDL_DestroyTexture(TextTexture); SDL_FreeSurface(TextSurface);
        std::cout << "DRAW TEXT DONE\n";

        SDL_RenderPresent(Renderer);
        if (Font) { TTF_CloseFont(Font); Font = nullptr; }
    }


    // #################################################


    void WaitForExit()
    {
        SDL_Event e;
        bool running = true;
        while (running)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT) { running = false; }
            }
            //SDL_RenderPresent(Renderer);
            //SDL_UpdateWindowSurface(Window);
            SDL_Delay(16);
        }
    }


    // #################################################


    ysxSDL_CandleGraphPlot(uint16_t W, uint16_t H)
    {
        Width = W; Height = H;
        if (SDL_Init(SDL_INIT_VIDEO) < 0) { std::cerr << "SDL could not initialize: " << SDL_GetError() << '\n'; return; }
        Window = SDL_CreateWindow("Candle Chart", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
        if (!Window) { std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n'; return; }
        Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED); if (!Renderer) { std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n'; return; }
        if (TTF_Init() == -1) { std::cerr << "TTF_Init failed: " << TTF_GetError() << '\n'; return; }
    }

    ~ysxSDL_CandleGraphPlot()
    {
        if (Renderer) { SDL_DestroyRenderer(Renderer); }
        if (Window) { SDL_DestroyWindow(Window); }
        SDL_Quit();
        TTF_Quit();
    }
};


// ###############################################################################################################################################################################

#endif
