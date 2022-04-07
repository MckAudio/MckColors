#pragma once
#include <gtkmm.h>
#include <vector>
#include <optional>

class MyWindow : public Gtk::Window
{
    enum class Luminance {
        BT_709 = 0,
        BT_601,
        BT_PERC,
        SRGB,
        LENGTH
    };
    const std::vector<std::string> LuminanceModes { "Photometric/Digital", "Perceived #1", "Perceived #2", "sRGB"};

    public:
        MyWindow();
        void UpdateLabels();
    private:
        void DisplayLuminance();
        std::optional<double> CalculateLuminance(const Gdk::RGBA &color, Luminance lumType);
        double CalculateSrgbLuminance(const Gdk::RGBA &color);
        void DisplayHue();
        
        void on_button_color_opened(const Gdk::RGBA &color);
        void on_button_color_set();
        void on_button_hi_clicked();
        void on_button_quit_clicked();
        void on_lum_switch_clicked();

        Gtk::ColorButton m_btnColor;
        Gtk::Button m_btnHi;
        Gtk::Button m_btnQuit;
        Gtk::Grid m_grid;
        Gtk::Label m_lumLabel;
        Gtk::Label m_hueLabel;
        std::vector<Gtk::CheckButton> m_lumBtns;
        Gtk::Box m_lumBox;

        Gdk::RGBA m_color;
        Luminance m_lumType;
};