#pragma once

#include "Deque.h"
#include "Button.h"
#include "Output.h"
#include "T9Tree.h"
#include <string>

class Keypad {
private:
    enum LetterCaseMode {
        UPPERCASE,
        LOWERCASE,
        UPPERCASE_FIRST
    };
    LetterCaseMode caseMode = UPPERCASE_FIRST;

    const int COLS = 3;
    const int ROWS = 4;
    GtkWidget* table = nullptr;
    GtkWidget* selection = nullptr;
    Button buttons[4][3];
    Button& toggleCaseButton;
    T9Tree& tree;
    Output& output;
    std::string LABELS[4][3] = {
        { "1\n<<<", "2\nABC", "3\nDEF" },
        { "4\nGHI", "5\nJKL", "6\nMNO" },
        { "7\nPQRS", "8\nTUV", "9\nWXYZ" },
        { "*\nAa", "0\n_", "#\nclear" }
    };
    std::string input, inputCase;
    int predictionCount = 0;

    static void staticHandler(GtkWidget* widget, gpointer instance)
    {
        ((Keypad*)instance)->handler(widget, NULL);
    }

    void handler(GtkWidget* widget, gpointer data)
    {
        int digit = *(int*)g_object_get_data(G_OBJECT(widget), "digit");
        switch (digit) {
            case 1:
                if (input.length() > 0) {
                    input.pop_back();
                    inputCase.pop_back();
                } else {
                    input = output.getLastWord();
                    inputCase = input;
                    input = T9Tree::digitize(input);
                }
                break;
            case 10:
                if (caseMode == LOWERCASE) {
                    caseMode = UPPERCASE_FIRST;
                    toggleCaseButton.setLabel("*\nAa");
                } else if (caseMode == UPPERCASE_FIRST) {
                    caseMode = UPPERCASE;
                    toggleCaseButton.setLabel("*\nAA");
                } else {
                    caseMode = LOWERCASE;
                    toggleCaseButton.setLabel("*\naa");
                }
                break;
            case 11:
                output.appendText(gtk_combo_box_text_get_active_text(
                    GTK_COMBO_BOX_TEXT(selection)
                ), true);
                input = "";
                inputCase = "";
                break;
            case 12:
                input = "";
                inputCase = "";
                output.setText("");
                caseMode = UPPERCASE_FIRST;
                toggleCaseButton.setLabel("*\nAa");
                break;
            default:
                input += digit + T9Tree::NUMERIC_ASCII_OFFSET;
                inputCase += (caseMode == LOWERCASE) ? 'a': 'A';
                if (caseMode == UPPERCASE_FIRST) {
                    caseMode = LOWERCASE;
                    toggleCaseButton.setLabel("*\naa");
                }
        }
        
        Deque<std::string> results = tree.findWords(input);
        while (predictionCount > 0) {
            gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(selection), 0);
            predictionCount--;
        }
        if (results.empty() && input.length() > 0) {
            input.pop_back();
            inputCase.pop_back();
            results = tree.findWords(input);
        }
        while (!results.empty()) {
            std::string result = results.pop_front();
            for (int i = 0; i < result.length(); i++) {
                if (std::isupper(inputCase[i])) {
                    result[i] = std::toupper(result[i]);
                }
            }
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(selection),
                                           result.c_str());
            predictionCount++;
        }
        gtk_combo_box_set_active(GTK_COMBO_BOX(selection), 0);
    }
    
public:
    Keypad(T9Tree& tree, Output output) :
        tree(tree),
        output(output),
        toggleCaseButton(buttons[3][0]),
        table(gtk_table_new(ROWS, COLS, TRUE)),
        selection(gtk_combo_box_text_new())
    {
        int i = 1;
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLS; x++, i++) {
                buttons[y][x].setDigit(i);
                buttons[y][x].setLabel(LABELS[y][x]);
                buttons[y][x].attach(table, x, y, staticHandler, this);
            }
        }

        gtk_widget_modify_font(
            gtk_bin_get_child(GTK_BIN(selection)),
            pango_font_description_from_string("Sans 20")
        );
    }

    void attach(GtkWidget* box)
    {
        gtk_box_pack_start(GTK_BOX(box), selection, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(box), table, TRUE, TRUE, 0);

        gtk_widget_show(selection);
        gtk_widget_show(table);
    }
};
