#include "Color.hpp"
#include <cmath>

unsigned Mck::Color::CalculateHue(const Gdk::RGBA &color)
{
    return CalculateHue(color.get_red(), color.get_green(), color.get_blue());
}
unsigned Mck::Color::CalculateHue(double red, double green, double blue)
{
    double max = std::max({red, green, blue});
    double min = std::min({red, green, blue});
    double hue = 0.0;
    if (red >= max)
    {
        hue = (green - blue) / (max - min);
    }
    else if (green >= max)
    {
        hue = 2.0 + (blue - red) / (max - min);
    }
    else
    {
        hue = 4.0 + (red - green) / (max - min);
    }
    hue = static_cast<unsigned>(std::round(360.0 + hue * 60.0)) % 360;
    return hue;
}

double Mck::Color::CalculateSaturation(const Gdk::RGBA &color)
{
    return CalculateSaturation(color.get_red(), color.get_green(), color.get_blue());
}
double Mck::Color::CalculateSaturation(double red, double green, double blue)
{
    double max = std::max({red, green, blue});
    double min = std::min({red, green, blue});
    if (max == min)
    {
        return 0.0;
    }
    else
    {
        if (CalculateLuminance(red, green, blue) <= 0.5)
        {
            return (max - min) / (max + min);
        }
        else
        {
            return (max - min) / (2.0 - max - min);
        }
    }
}

double Mck::Color::CalculateLuminance(const Gdk::RGBA &color)
{
    return CalculateLuminance(color.get_red(), color.get_green(), color.get_blue());
}
double Mck::Color::CalculateLuminance(double red, double green, double blue)
{
    double max = std::max({red, green, blue});
    double min = std::min({red, green, blue});
    return (max + min) / 2.0;
}

std::string Mck::Color::CalculateHex(const Gdk::RGBA &color)
{
    return CalculateHex(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
}
std::string Mck::Color::CalculateHex(double red, double green, double blue, double alpha)
{
    unsigned char r = static_cast<unsigned int>(std::round(std::min(1.0, std::max(0.0, red)) * 255.0));
    unsigned char g = static_cast<unsigned int>(std::round(std::min(1.0, std::max(0.0, green)) * 255.0));
    unsigned char b = static_cast<unsigned int>(std::round(std::min(1.0, std::max(0.0, blue)) * 255.0));
    unsigned char a = static_cast<unsigned int>(std::round(std::min(1.0, std::max(0.0, alpha)) * 255.0));

    char buf[10];
    std::sprintf(buf, "#%02X%02X%02X%02X\n", r, g, b, a);
    return std::string(buf);
}

Mck::Color::Color()
    : m_red(0.0),
      m_green(0.0),
      m_blue(0.0),
      m_alpha(1.0)
{
    Update();
}

Mck::Color::Color(int red, int green, int blue, int alpha)
{
    m_red = static_cast<double>(std::min(255, std::max(0, red))) / 255.0;
    m_green = static_cast<double>(std::min(255, std::max(0, green))) / 255.0;
    m_blue = static_cast<double>(std::min(255, std::max(0, blue))) / 255.0;
    m_alpha = static_cast<double>(std::min(255, std::max(0, alpha))) / 255.0;
    Update();
}
Mck::Color::Color(double red, double green, double blue, double alpha)
{
    m_red = std::min(1.0, std::max(0.0, red));
    m_green = std::min(1.0, std::max(0.0, green));
    m_blue = std::min(1.0, std::max(0.0, blue));
    m_alpha = std::min(1.0, std::max(0.0, alpha));
    Update();
}

Mck::Color::Color(const Gdk::RGBA &color)
    : m_red(color.get_red()),
      m_green(color.get_green()),
      m_blue(color.get_blue()),
      m_alpha(color.get_alpha())
{
    Update();
}

void Mck::Color::Update()
{
    m_hex = CalculateHex(m_red, m_green, m_blue, m_alpha);
    m_hue = CalculateHue(m_red, m_green, m_blue);
    m_saturation = CalculateSaturation(m_red, m_green, m_blue);
    m_luminance = CalculateLuminance(m_red, m_green, m_blue);
}

std::string Mck::Color::PrintRGB()
{
    auto r = static_cast<unsigned>(std::round(m_red * 255.0));
    auto g = static_cast<unsigned>(std::round(m_green * 255.0));
    auto b = static_cast<unsigned>(std::round(m_blue * 255.0));
    char buf[64];
    std::sprintf(buf, "rgb(%d, %d, %d)\n", r, g, b);
    return std::string(buf);
}

std::string Mck::Color::PrintHSL()
{
    auto s = static_cast<unsigned>(std::round(m_saturation * 100.0));
    auto l = static_cast<unsigned>(std::round(m_luminance * 100.0));
    char buf[64];
    std::sprintf(buf, "hsl(%d, %d%%, %d%%)\n", m_hue, s, l);
    return std::string(buf);
}