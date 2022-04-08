#include "MyWindow.hpp"

#include <cstdio>
#include <cmath>
#include <string>

Mck::MyWindow::MyWindow()
    : m_btnColor(),
      m_btnStar("Star Color"),
      m_btnQuit("Leave app"),
      m_labelHex(),
      m_labelRgb(),
      m_labelHsl(),
      m_color(0, 127, 200)
{
    set_title("First GTK4 app");
    set_default_size(300, 200);

    m_grid.set_margin(20);
    m_grid.set_column_spacing(20);
    m_grid.set_row_spacing(10);
    set_child(m_grid);

    m_btnColor.signal_color_activated().connect(sigc::mem_fun(*this, &Mck::MyWindow::on_button_color_opened));
    m_btnColor.signal_color_set().connect(sigc::mem_fun(*this, &Mck::MyWindow::on_button_color_set));
    m_btnColor.set_rgba(m_color.GetRGBA());
    m_grid.attach(m_btnColor, 0, 0);

    m_btnStar.signal_clicked().connect(sigc::mem_fun(*this, &Mck::MyWindow::on_button_star_clicked));
    m_btnStar.set_icon_name("non-starred");
    m_grid.attach(m_btnStar, 1, 0);

    m_btnQuit.signal_clicked().connect(sigc::mem_fun(*this, &Mck::MyWindow::on_button_quit_clicked));
    m_btnQuit.set_icon_name("application-exit");
    m_grid.attach(m_btnQuit, 2, 0);

    m_grid.attach(m_labelHex, 0, 1);
    m_grid.attach(m_labelRgb, 0, 2);
    m_grid.attach(m_labelHsl, 0, 3);

    UpdateLabels();
}

void Mck::MyWindow::UpdateLabels()
{
    if (m_colors.contains(m_color.GetHex())) {
        m_btnStar.set_icon_name("starred");
    } else {
        m_btnStar.set_icon_name("non-starred");
    }

    m_labelHex.set_label(m_color.GetHex());
    m_labelRgb.set_label(m_color.PrintRGB());
    m_labelHsl.set_label(m_color.PrintHSL());
}


void Mck::MyWindow::on_button_color_opened(const Gdk::RGBA &color)
{
}
void Mck::MyWindow::on_button_color_set()
{
    m_color = Color(m_btnColor.get_rgba());
    std::printf("You chose a new color: %f - %f - %f\n", m_color.GetRed(), m_color.GetGreen(), m_color.GetBlue());
    UpdateLabels();
}
void Mck::MyWindow::on_button_star_clicked()
{
    std::string colHex = m_color.GetHex();
    if (m_colors.contains(colHex)) {
        m_colors.erase(colHex);
    } else {
        m_colors[colHex] = m_color;
    }
    UpdateLabels();
}
void Mck::MyWindow::on_button_quit_clicked()
{
    close();
}