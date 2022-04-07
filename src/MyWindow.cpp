#include "MyWindow.hpp"
#include <cstdio>
#include <cmath>
#include <string>

MyWindow::MyWindow()
    : m_btnColor(),
      m_btnHi("Say something"),
      m_btnQuit("Leave app"),
      m_lumLabel("Luminance"),
      m_hueLabel("Hue"),
      m_color("#ff5500"),
      m_lumType(Luminance::BT_601)
{
    set_title("First GTK4 app");
    set_default_size(300, 200);

    m_grid.set_margin(20);
    m_grid.set_column_spacing(20);
    m_grid.set_row_spacing(20);
    set_child(m_grid);

    m_btnColor.signal_color_activated().connect(sigc::mem_fun(*this, &MyWindow::on_button_color_opened));
    m_btnColor.signal_color_set().connect(sigc::mem_fun(*this, &MyWindow::on_button_color_set));
    m_btnColor.set_rgba(m_color);
    m_grid.attach(m_btnColor, 0, 0, 2, 1);

    m_btnHi.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_hi_clicked));
    m_btnHi.set_icon_name("starred");
    m_grid.attach(m_btnHi, 2, 0);

    m_btnQuit.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_quit_clicked));
    m_btnQuit.set_icon_name("application-exit");
    m_grid.attach(m_btnQuit, 3, 0);

    // Luminance Buttons
    m_lumBox.set_orientation(Gtk::Orientation::VERTICAL);
    m_lumBox.set_spacing(10);
    m_lumBtns.resize(static_cast<std::size_t>(Luminance::LENGTH));
    for (unsigned i = 0; i < static_cast<unsigned>(Luminance::LENGTH); i++)
    {
        if (i != 0)
        {
            m_lumBtns[i].set_group(m_lumBtns[0]);
        }
        m_lumBtns[i].set_active(i == static_cast<unsigned>(m_lumType));
        m_lumBtns[i].set_label(LuminanceModes[i]);
        m_lumBtns[i].signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::on_lum_switch_clicked));
        m_lumBox.append(m_lumBtns[i]);
    }
    m_grid.attach(m_lumBox, 0, 1);

    m_grid.attach(m_lumLabel, 1, 1);
    m_grid.attach(m_hueLabel, 2, 1);

    UpdateLabels();
}

void MyWindow::UpdateLabels()
{
    DisplayLuminance();
    DisplayHue();
}

void MyWindow::DisplayLuminance()
{
    auto ret = CalculateLuminance(m_color, m_lumType);
    if (ret.has_value()) {
        double lum = std::round(ret.value() * 100.0 * 10.0) / 10.0;
        m_lumLabel.set_label(std::to_string(lum) + " %");
    } else {
        m_lumLabel.set_label("INVALID");
    }
}


std::optional<double> MyWindow::CalculateLuminance(const Gdk::RGBA &color, Luminance lumType)
{
    switch (lumType)
    {
    case Luminance::BT_709:
        return (0.2126 * color.get_red() + 0.7152 * color.get_green() + 0.0722 * color.get_blue());
        break;
    case Luminance::BT_601:
        return (0.299 * color.get_red() + 0.587 * color.get_green() + 0.114 * color.get_blue());
    case Luminance::BT_PERC:
        return std::sqrt(std::pow(0.299 * color.get_red(), 2.0) + std::pow(0.587 * color.get_green(), 2.0) + std::pow(0.114 * color.get_blue(), 2.0));
    case Luminance::SRGB:
        return CalculateSrgbLuminance(color);
    default:
        break;
    }
    return {};
}

// https://stackoverflow.com/a/13558570
double MyWindow::CalculateSrgbLuminance(const Gdk::RGBA &color)
{
    // sRGB luminance(Y) values
    const double rY = 0.212655;
    const double gY = 0.715158;
    const double bY = 0.072187;

    // Inverse of sRGB "gamma" function. (approx 2.2)
    auto inv_gam_sRGB = [](double c)
    {
        if (c <= 0.04045)
            return c / 12.92;
        else
            return std::pow(((c + 0.055) / (1.055)), 2.4);
    };

    // sRGB "gamma" function (approx 2.2)
    auto gam_sRGB = [](double v)
    {
        if (v <= 0.0031308)
            v *= 12.92;
        else
            v = 1.055 * std::pow(v, 1.0 / 2.4) - 0.055;
        return v;
    };

    // GRAY VALUE ("brightness")
    return gam_sRGB(
        rY * inv_gam_sRGB(color.get_red()) +
        gY * inv_gam_sRGB(color.get_green()) +
        bY * inv_gam_sRGB(color.get_blue()));
}

void MyWindow::DisplayHue()
{
    double r = m_color.get_red();
    double g = m_color.get_green();
    double b = m_color.get_blue();
    double max = std::max({ r, g, b });
    double min = std::min({ r, g, b });
    double hue = 0.0;
    if (r >= max) {
        hue = (g-b)/(max-min);
    } else if (g >= max) {
        hue = 2.0 + (b-r)/(max-min);
    } else {
        hue = 4.0 + (r-g)/(max-min);
    }
    hue *= 60.0;

    m_hueLabel.set_label(std::to_string(hue) + " deg");
}

void MyWindow::on_button_color_opened(const Gdk::RGBA &color)
{
}
void MyWindow::on_button_color_set()
{
    m_color = m_btnColor.get_rgba();
    std::printf("You chose a new color: %f - %f - %f\n", m_color.get_red(), m_color.get_green(), m_color.get_blue());
    UpdateLabels();
}
void MyWindow::on_button_hi_clicked()
{
    std::printf("By the order of the Peaky Blinders!\n");
}
void MyWindow::on_button_quit_clicked()
{
    close();
}
void MyWindow::on_lum_switch_clicked()
{
    for (unsigned i = 0; i < m_lumBtns.size(); i++)
    {
        if (m_lumBtns[i].get_active())
        {
            m_lumType = static_cast<Luminance>(i);
            UpdateLabels();
            return;
        }
    }
}