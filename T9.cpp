#include "T9Tree.h"
#include "Keypad.h"
#include "Output.h"
#include <fstream>
#include <iostream>
#include <string>
#include <gtk/gtk.h>

void destroy(GtkWidget* widget, gpointer data)
{
    gtk_main_quit();
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    if (argc < 2) {
        std::cerr << "No dictionary file selected" << std::endl;
        return 1;
    }

    T9Tree tree;
    std::ifstream dictionary(argv[1]);
    std::string line;
    while (dictionary >> line) {
        tree.insert(line);
    }
    dictionary.close();

    Output output;
    Keypad keypad(tree, output);

    GtkWidget* window;
    GtkWidget* box;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "T9 input demo");
    gtk_window_resize(GTK_WINDOW(window), 300, 400);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    box = gtk_vbox_new(FALSE, 0);
    output.attach(box);
    keypad.attach(box);
    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_widget_show(box);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
