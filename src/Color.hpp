#pragma once
#include <gdkmm/rgba.h>
#include <string>

namespace Mck
{
    class Color
    {
    public:
        static double CalculateHue(const Gdk::RGBA &color);
        static double CalculateHue(double red, double green, double blue);

        static std::string CalculateHex(const Gdk::RGBA &color);
        static std::string CalculateHex(double red, double green, double blue, double alpha = 1.0);

        Color();
        Color(int red, int green, int blue, int alpha = 255);
        Color(double red, double green, double blue, double alpha = 1.0);
        Color(const Gdk::RGBA &color);

        std::string GetHex();
        double GetHue();

        double GetRed() { return m_red; };
        double GetGreen() { return m_green; };
        double GetBlue() { return m_blue; };
        double GetAlpha() { return m_alpha; };

        Gdk::RGBA GetRGBA() { return Gdk::RGBA(m_red, m_blue, m_green, m_alpha); };

    private:
        double m_red;
        double m_green;
        double m_blue;
        double m_alpha;
    };
}