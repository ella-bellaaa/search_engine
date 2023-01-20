//
// Created by Ella Grace Collard on 11/14/22.
//

#include "doc.h"

doc::doc(const string &title, const string &publication, const string &datePublished, const string& txt, const int& id) : title(title),
                                                                                        publication(publication),
                                                                                        date_published(datePublished),
                                                                                        text(txt),
                                                                                        id(id) {}

bool doc::operator==(const doc &rhs) const {
    return id == rhs.id;
}

bool doc::operator!=(const doc &rhs) const {
    return !(rhs == *this);
}

const string &doc::getTitle() const {
    return title;
}

void doc::setTitle(const string &title) {
    doc::title = title;
}

const string &doc::getPublication() const {
    return publication;
}

void doc::setPublication(const string &publication) {
    doc::publication = publication;
}

const string &doc::getDatePublished() const {
    return date_published;
}

void doc::setDatePublished(const string &datePublished) {
    date_published = datePublished;
}

const string &doc::getText() const {
    return text;
}

void doc::setText(const string &text) {
    doc::text = text;
}

int doc::getId() const {
    return id;
}

void doc::setId(int id) {
    doc::id = id;
}
