//
// Created by Ella Grace Collard on 11/14/22.
//

#ifndef FINALPROJEXAMPLES_DOC_H
#define FINALPROJEXAMPLES_DOC_H
using namespace std;
#include <string>

class doc {
private:
    string title;
    string publication;
    string date_published;
    string text;
    int id;
public:
    const string &getText() const;

    void setText(const string &text);

    int getId() const;

    void setId(int id);

    const string &getTitle() const;

    void setTitle(const string &title);

    const string &getPublication() const;

    void setPublication(const string &publication);

    const string &getDatePublished() const;

    void setDatePublished(const string &datePublished);

    bool operator==(const doc &rhs) const;

    bool operator!=(const doc &rhs) const;

    doc(const string &title, const string &publication, const string &datePublished, const string& text, const int& id);
};
#endif //FINALPROJEXAMPLES_DOC_H
