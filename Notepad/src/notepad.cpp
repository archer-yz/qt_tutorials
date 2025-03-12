#include "notepad.hpp"

#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#endif
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#endif

Notepad::Notepad(QWidget* parent) : QMainWindow(parent)
{
    this->setGeometry(0, 0, 800, 400);
    this->setWindowTitle("NotePad");
    this->setWindowIcon(QIcon(":/images/key-logo.ico"));

    auto central_widget = new QWidget(this);
    auto top_layout = new QVBoxLayout();
    this->text_edit = new QTextEdit(central_widget);

    top_layout->addWidget(this->text_edit);

    central_widget->setLayout(top_layout);
    this->setCentralWidget(central_widget);

    create_actions();
    create_menus();
    create_toolbars();
    create_connections();

    statusBar()->showMessage(tr("Ready"));
    setMinimumSize(160, 160);
}

Notepad::~Notepad()
{
}

/* cSpell:ignore saveas */
void Notepad::create_menus()
{
    file_menu = menuBar()->addMenu(tr("&File"));
    edit_menu = menuBar()->addMenu(tr("&Edit"));
    about_menu = menuBar()->addMenu(tr("&About"));

    file_menu->addAction(new_action);
    file_menu->addAction(open_action);
    file_menu->addAction(save_action);
    file_menu->addAction(saveas_action);
    file_menu->addAction(print_action);
    file_menu->addSeparator();
    file_menu->addAction(exit_action);

    edit_menu->addAction(copy_action);
    edit_menu->addAction(cut_action);
    edit_menu->addAction(paste_action);
    edit_menu->addSeparator();
    edit_menu->addAction(undo_action);
    edit_menu->addAction(redo_action);
    edit_menu->addAction(font_action);

    about_menu->addAction(about_action);
}

void Notepad::create_actions()
{
    new_action = new QAction(QIcon(":/images/new.png"), tr("New"), this);
    new_action->setShortcut(QKeySequence::New);
    new_action->setToolTip(tr("New text document"));
    new_action->setStatusTip(tr("Create a new file"));

    open_action = new QAction(QIcon(":/images/open.png"), tr("Open"), this);
    open_action->setShortcut(QKeySequence::Open);
    open_action->setToolTip(tr("Open file"));
    open_action->setStatusTip(tr("Open file"));

    save_action = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
    save_action->setShortcut(QKeySequence::Save);
    save_action->setToolTip(tr("Save file"));
    save_action->setStatusTip(tr("Save file"));

    saveas_action = new QAction(QIcon(":/images/save_as.png"), tr("Save as"), this);
    saveas_action->setShortcut(QKeySequence::SaveAs);
    saveas_action->setToolTip(tr("Save file as"));
    saveas_action->setStatusTip(tr("Save file as"));

    print_action = new QAction(QIcon(":/images/print.png"), tr("Print"), this);
    print_action->setShortcut(QKeySequence::Print);
    print_action->setToolTip(tr("Print file"));
    print_action->setStatusTip(tr("Print file"));

    exit_action = new QAction(QIcon(":/images/exit.png"), tr("Exit"), this);
    exit_action->setShortcut(QKeySequence::Close);
    exit_action->setToolTip(tr("Exit notepad"));
    exit_action->setStatusTip(tr("Exit notepad"));

    copy_action = new QAction(QIcon(":/images/copy.png"), tr("Copy"), this);
    copy_action->setShortcut(QKeySequence::Copy);
    copy_action->setToolTip(tr("Copy"));

    cut_action = new QAction(QIcon(":/images/cut.png"), tr("Cut"), this);
    cut_action->setShortcut(QKeySequence::Cut);
    cut_action->setToolTip(tr("Cut"));

    paste_action = new QAction(QIcon(":/images/paste.png"), tr("Paste"), this);
    paste_action->setShortcut(QKeySequence::Paste);
    paste_action->setToolTip(tr("Paste"));

    undo_action = new QAction(QIcon(":/images/edit_undo.png"), tr("Undo"), this);
    undo_action->setShortcut(QKeySequence::Undo);
    undo_action->setToolTip(tr("Undo"));

    redo_action = new QAction(QIcon(":/images/edit_redo.png"), tr("Redo"), this);
    redo_action->setShortcut(QKeySequence::Redo);
    redo_action->setToolTip(tr("Redo"));

    font_action = new QAction(QIcon(":/images/font.png"), tr("Font"), this);
    font_action->setShortcut(QKeySequence("Ctrl+F"));
    font_action->setToolTip(tr("Font"));

    bold_action = new QAction(QIcon(":/images/bold.png"), tr("Bold"), this);
    bold_action->setCheckable(true);
    bold_action->setShortcut(QKeySequence::Bold);
    bold_action->setToolTip(tr("Bold"));

    italic_action = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
    italic_action->setCheckable(true);
    italic_action->setShortcut(QKeySequence::Italic);
    italic_action->setToolTip(tr("Italic"));

    underline_action = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
    underline_action->setCheckable(true);
    underline_action->setShortcut(QKeySequence::Underline);
    underline_action->setToolTip(tr("Underline"));

    about_action = new QAction(QIcon(":/images/info.png"), tr("About"), this);
    about_action->setToolTip(tr("About Notepad"));

#if !QT_CONFIG(clipboard)
    copy_action->setEnabled(false);
    paste_action->setEnabled(false);
    cut_action->setEnabled(false);
#endif

#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
    print_action->setEnabled(false);
#endif
}

void Notepad::create_toolbars()
{
    auto topToolBar = addToolBar(tr("toolBarArea"));
    topToolBar->setMovable(false);
    topToolBar->addAction(new_action);
    topToolBar->addAction(open_action);
    topToolBar->addAction(save_action);
    topToolBar->addAction(saveas_action);
    topToolBar->addAction(print_action);
    topToolBar->addSeparator();
    topToolBar->addAction(copy_action);
    topToolBar->addAction(cut_action);
    topToolBar->addAction(paste_action);
    topToolBar->addAction(undo_action);
    topToolBar->addAction(redo_action);
    topToolBar->addSeparator();
    topToolBar->addAction(font_action);
    topToolBar->addAction(bold_action);
    topToolBar->addAction(italic_action);
    topToolBar->addAction(underline_action);
    topToolBar->addSeparator();
    topToolBar->addAction(about_action);
}

void Notepad::create_connections()
{
    connect(this->new_action, &QAction::triggered, this, &Notepad::newDocument);
    connect(this->open_action, &QAction::triggered, this, &Notepad::open);
    connect(this->save_action, &QAction::triggered, this, &Notepad::save);
    connect(this->saveas_action, &QAction::triggered, this, &Notepad::saveAs);
    connect(this->print_action, &QAction::triggered, this, &Notepad::print);
    connect(this->exit_action, &QAction::triggered, this, &QWidget::close);
#if QT_CONFIG(clipboard)
    connect(this->text_edit, &QTextEdit::copyAvailable, this->copy_action, &QAction::setEnabled);
    connect(this->copy_action, &QAction::triggered, this->text_edit, &QTextEdit::copy);
    connect(this->cut_action, &QAction::triggered, this->text_edit, &QTextEdit::cut);
    connect(this->paste_action, &QAction::triggered, this->text_edit, &QTextEdit::paste);
#endif
    connect(this->text_edit, &QTextEdit::undoAvailable, this->undo_action, &QAction::setEnabled);
    connect(this->undo_action, &QAction::triggered, this->text_edit, &QTextEdit::undo);
    connect(this->text_edit, &QTextEdit::redoAvailable, this->redo_action, &QAction::setEnabled);
    connect(this->redo_action, &QAction::triggered, this->text_edit, &QTextEdit::redo);

    connect(this->font_action, &QAction::triggered, this, &Notepad::selectFont);
    connect(this->bold_action, &QAction::triggered, this, &Notepad::setFontBold);
    connect(this->underline_action, &QAction::triggered, this, &Notepad::setFontUnderline);
    connect(this->italic_action, &QAction::triggered, this, &Notepad::setFontItalic);
    connect(this->about_action, &QAction::triggered, this, &Notepad::about);
}

void Notepad::newDocument()
{
    current_file.clear();
    this->text_edit->setText(QString());
}

void Notepad::open()
{
    auto file_name = QFileDialog::getOpenFileName(this, "Open the file");
    if (file_name.isEmpty())
        return;
    QFile file(file_name);
    current_file = file_name;
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(file_name);
    QTextStream in(&file);
    auto text = in.readAll();
    this->text_edit->setText(text);
    file.close();
}

void Notepad::save()
{
    QString file_name;
    if (current_file.isEmpty())
    {
        file_name = QFileDialog::getSaveFileName(this, "Save");
        if (file_name.isEmpty())
            return;
        current_file = file_name;
    }
    else
    {
        file_name = current_file;
    }
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(file_name);
    QTextStream out(&file);
    auto text = this->text_edit->toPlainText();
    out << text;
    file.close();
}

void Notepad::saveAs()
{
    auto file_name = QFileDialog::getSaveFileName(this, "Save as");
    if (file_name.isEmpty())
        return;

    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    current_file = file_name;
    setWindowTitle(file_name);
    QTextStream out(&file);
    auto text = this->text_edit->toPlainText();
    out << text;
    file.close();
}

void Notepad::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
    this->text_edit->print(&printDev);
#endif // QT_CONFIG(printer)
}

void Notepad::selectFont()
{
    bool font_selected;
    auto font = QFontDialog::getFont(&font_selected, this);
    if (font_selected)
        this->text_edit->setFont(font);
}

void Notepad::setFontBold(bool bold)
{
    bold ? this->text_edit->setFontWeight(QFont::Bold) :
           this->text_edit->setFontWeight(QFont::Normal);
}

void Notepad::setFontUnderline(bool underline)
{
    this->text_edit->setFontUnderline(underline);
}

void Notepad::setFontItalic(bool italic)
{
    this->text_edit->setFontItalic(italic);
}

void Notepad::about()
{
    QMessageBox::about(this, tr("About Notepad"),
    tr("The <b>Notepad</b> example demonstrates how to code a basic text editor using QtWidgets"));
}
