#pragma once
#include <gdkmm/rgba.h>
#include <string>

namespace Mck
{
    class Color
    {
    public:
        static unsigned CalculateHue(const Gdk::RGBA &color);
        static unsigned CalculateHue(double red, double green, double blue);

        static double CalculateSaturation(const Gdk::RGBA &color);
        static double CalculateSaturation(double red, double green, double blue);

        static double CalculateLuminance(const Gdk::RGBA &color);
        static double CalculateLuminance(double red, double green, double blue);

        static std::string CalculateHex(const Gdk::RGBA &color);
        static std::string CalculateHex(double red, double green, double blue, double alpha = 1.0);

        Color();
        Color(int red, int green, int blue, int alpha = 255);
        Color(double red, double green, double blue, double alpha = 1.0);
        Color(const Gdk::RGBA &color);

        std::string GetHex() { return m_hex; };

        double GetRed() { return m_red; };
        double GetGreen() { return m_green; };
        double GetBlue() { return m_blue; };
        double GetAlpha() { return m_alpha; };

        unsigned GetHue() { return m_hue; };
        double GetSaturation() { return m_saturation; };
        double GetLuminance() { return m_luminance; };

        Gdk::RGBA GetRGBA() { return Gdk::RGBA(m_red, m_blue, m_green, m_alpha); };

        std::string PrintRGB();
        std::string PrintHSL();

    private:
        void Update();

        double m_red;
        double m_green;
        double m_blue;
        double m_alpha;

        unsigned m_hue;
        double m_saturation;
        double m_luminance;

        std::string m_hex;
    };
}