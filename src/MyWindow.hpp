#pragma once
#include "Color.hpp"

#include <gtkmm.h>
#include <vector>
#include <optional>
#include <map>

namespace Mck
{
    class MyWindow : public Gtk::Window
    {
    public:
        MyWindow();
        void UpdateLabels();

    private:
        void on_button_color_opened(const Gdk::RGBA &color);
        void on_button_color_set();
        void on_button_star_clicked();
        void on_button_quit_clicked();

        Gtk::ColorButton m_btnColor;
        Gtk::Button m_btnStar;
        Gtk::Button m_btnQuit;
        Gtk::Grid m_grid;
        Gtk::Label m_labelHex;
        Gtk::Label m_labelRgb;
        Gtk::Label m_labelHsl;

        Color m_color;
        std::map<std::string, Color> m_colors;
    };
}