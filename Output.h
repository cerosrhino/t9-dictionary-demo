#pragma once

#include <string>
#include <gtk/gtk.h>

class Output {
private:
    const int WIDTH = 280;
    const int HEIGHT = 100;
    GtkWidget* label = nullptr;
    std::string text;
    
public:
    Output() :
        label(gtk_label_new(""))
    {
        gtk_widget_modify_font(
            label,
            pango_font_description_from_string("Sans 20")
        );
        
        gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
        gtk_widget_set_size_request(label, WIDTH, HEIGHT);
    }

    void attach(GtkWidget* box)
    {
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

        gtk_widget_show(label);
    }

    void setText(std::string text)
    {
        this->text = text;
        gtk_label_set_text(GTK_LABEL(label), text.c_str());
    }

    void appendText(std::string input, bool addSpaceIfRequired = false)
    {
        if (text.length() > 0 && addSpaceIfRequired) {
            text += ' ';
        }
        setText(text + input);
    }

    std::string getText()
    {
        return text;
    }

    std::string getLastWord()
    {
        std::string word;

        std::string::size_type n;
        n = text.rfind(" ");
        if (n != std::string::npos) {
            word = text.substr(n + 1);
            setText(text.substr(0, n));
        } else if (text.length() > 0) {
            word = text;
            setText("");
        }

        return word;
    }
};
