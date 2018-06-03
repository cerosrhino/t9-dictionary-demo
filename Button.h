#pragma once

#include "Deque.h"
#include <cctype>
#include <gtk/gtk.h>

class Button {
private:
    GtkWidget* widget = nullptr;
    int digit;

public:
    Button() : widget(gtk_button_new_with_label("")) {}

    void setLabel(std::string labelText)
    {
        GtkWidget* label = gtk_bin_get_child(GTK_BIN(widget));
        gtk_label_set_text(GTK_LABEL(label), labelText.c_str());
        gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
        gtk_widget_modify_font(
            label,
            pango_font_description_from_string("Sans 20")
        );
    }

    void setDigit(int digit)
    {
        this->digit = digit;
        g_object_set_data(G_OBJECT(widget), "digit", &this->digit);
    }

    void attach(GtkWidget* table, int x, int y,
                void(*callback)(GtkWidget*, gpointer), gpointer context)
    {
        gtk_table_attach_defaults(GTK_TABLE(table), widget, x, x + 1, y, y + 1);
        
        g_signal_connect(widget, "clicked", G_CALLBACK(callback), context);

        gtk_widget_show(widget);
    }
};
