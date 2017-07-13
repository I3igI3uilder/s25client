// Copyright (c) 2005 - 2017 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.
#ifndef CTRLBUTTON_H_INCLUDED
#define CTRLBUTTON_H_INCLUDED

#pragma once

#include "ctrlBaseColor.h"
#include "ctrlText.h"

#include <string>

class MouseCoords;
class glArchivItem_Bitmap;
class glArchivItem_Font;

/// Buttonklasse
class ctrlButton : public Window
{
    public:
        ctrlButton(Window* parent, unsigned int id, unsigned short x, unsigned short y, unsigned short width, unsigned short height,
                   const TextureColor tc, const std::string& tooltip);
        ~ctrlButton() override;

        void SetEnabled(bool enable = true) { isEnabled = enable; }
        bool GetEnabled() const { return isEnabled; }
        TextureColor GetTexture() const { return tc; }
        void SetTexture(TextureColor tc) { this->tc = tc; }

        /// Setzt Tooltip
        void SetTooltip(const std::string& tooltip) { this->tooltip_ = tooltip; }
        /// Liefert Tooltip zurück
        std::string GetTooltip() const { return tooltip_; }
        /// Tauscht Tooltips
        void SwapTooltip(ctrlButton* otherBt);

        void SetChecked(bool checked) { this->isChecked = checked; }
        bool GetCheck() { return isChecked; }
        void SetIlluminated(bool illuminated) { this->isIlluminated = illuminated; }
        bool GetIlluminated() { return isIlluminated; }
        void SetBorder(bool hasBorder) { this->hasBorder = hasBorder; }

        bool Msg_MouseMove(const MouseCoords& mc) override;
        bool Msg_LeftDown(const MouseCoords& mc) override;
        bool Msg_LeftUp(const MouseCoords& mc) override;

    protected:
        /// Zeichnet Grundstruktur des Buttons
        void Draw_() override;
        /// Abgeleitete Klassen müssen erweiterten Button-Inhalt zeichnen
        virtual void DrawContent() const = 0;
        // Prüfen, ob bei gehighlighteten Button die Maus auch noch über dem Button ist
        void TestMouseOver();
        bool IsMouseOver(const int mouseX, const int mouseY) const;

    protected:

        /// Texturfarbe des Buttons
        TextureColor tc;
        /// Status des Buttons (gedrückt, erhellt usw. durch Maus ausgelöst)
        ButtonState state;
        /// Hat der Button einen 3D-Rand?
        bool hasBorder;
        /// Button dauerhaft gedrückt?
        bool isChecked;
        /// Button "erleuchtet"?
        bool isIlluminated;
        /// Button angeschalten?
        bool isEnabled;
};

/// Button mit Text
class ctrlTextButton : public ctrlButton, public ctrlBaseText
{
    public:

        ctrlTextButton(Window* parent, unsigned int id, unsigned short x, unsigned short y,
                       unsigned short width, unsigned short height, const TextureColor tc,
                       const std::string& text,  glArchivItem_Font* font, const std::string& tooltip);

    protected:

        /// Abgeleitete Klassen müssen erweiterten Button-Inhalt zeichnen (Text in dem Fall)
        void DrawContent() const override;
};


/// Button mit einem Bild
class ctrlImageButton : public ctrlButton
{
    public:

        ctrlImageButton(Window* parent, unsigned int id, unsigned short x, unsigned short y,
                        unsigned short width, unsigned short height, const TextureColor tc,
                        glArchivItem_Bitmap* const image, const std::string& tooltip);

    public:

        /// Setzt Bild des Buttons
        void SetImage(glArchivItem_Bitmap* image) { this->image = image; }
        /// Tauscht Bilder
        void SwapImage(ctrlImageButton* two) { std::swap(image, two->image); }
        /// Gibt Bild zurück
        glArchivItem_Bitmap* GetButtonImage() const { return image; }
        /// Ändert Farbfilter, mit dem dieses Bild gezeichnet werden soll
        void SetModulationColor(const unsigned modulation_color)
        { this->modulation_color = modulation_color; }


    protected:

        /// Abgeleitete Klassen müssen erweiterten Button-Inhalt zeichnen (Text in dem Fall)
        void DrawContent() const override;

    protected:

        /// Bild
        glArchivItem_Bitmap* image;
        /// Farbe mit der das Bild gezeichnet werden soll
        unsigned modulation_color;
};

/// Button mit Farbe
class ctrlColorButton : public ctrlButton, public ctrlBaseColor
{
    public:

        ctrlColorButton(Window* parent, unsigned int id, unsigned short x, unsigned short y,
                        unsigned short width, unsigned short height, const TextureColor tc,
                        unsigned int fillColor, const std::string& tooltip);

    protected:

        /// Abgeleitete Klassen müssen erweiterten Button-Inhalt zeichnen (Text in dem Fall)
        void DrawContent() const override;
};



#endif // CTRLBUTTON_H_INCLUDED
