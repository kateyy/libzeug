#include <propertyguizeug/ColorEditor.h>

#include <cassert>

#include <QApplication>
#include <QColorDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QRegExpValidator>
#include <QStyleOptionViewItem>

#include <reflectionzeug/ColorPropertyInterface.h>
#include <reflectionzeug/Color.h>

#include <propertyguizeug/ColorButton.h>

using namespace reflectionzeug;

namespace 
{

QColor toQColor(const Color & color)
{
    return {color.red(), color.green(), color.blue(), color.alpha()};
}

Color toColor(const QColor & color)
{
    return {color.red(), color.green(), color.blue(), color.alpha()};
}

} // namespace

namespace propertyguizeug
{

void ColorEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    ColorPropertyInterface & property)
{
    auto color = property.toColor();
    auto qcolor = toQColor(color);
    
    const auto alpha = property.option<bool>("alpha", true);
                  
    const auto metrics = option.widget->fontMetrics();
    const auto buttonSize = ColorButton::sizeFromFontHeight(metrics.height());
    auto buttonRect = QRect{option.rect.topLeft(), buttonSize};
    buttonRect.moveCenter({buttonRect.center().x(), option.rect.center().y()});
    const auto topLeft = buttonRect.topLeft();
    
    auto widget = option.widget;
    auto style = widget ? widget->style() : QApplication::style();
    
    ColorButton::paint(painter, topLeft, qcolor);

    auto rect = option.rect;
    rect.setLeft(option.rect.left() + 
                 buttonSize.width() + 4);

    
    style->drawItemText(
        painter,
        rect,
        Qt::AlignVCenter,
        option.palette,
        true,
        QString::fromStdString(property.toColor().toString(alpha)),
        QPalette::Text);
}
                      
ColorEditor::ColorEditor(ColorPropertyInterface * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_alpha{property->option<bool>("alpha", true)}
,   m_property{property}
{
    Color color = m_property->toColor();
    QColor qcolor = toQColor(color);
    
    m_lineEdit = new QLineEdit{this};
    m_lineEdit->setText(QString::fromStdString(m_property->toColor().toString(m_alpha)));
    
    m_button = new ColorButton{this, qcolor};
    
    boxLayout()->setSpacing(2);
    addWidget(m_button);
    addWidget(m_lineEdit);
    setFocusProxy(m_lineEdit);

    auto hexRegex = m_alpha ? "#[0-9A-Fa-f]{8}" : "#[0-9A-Fa-f]{6}";
    auto validator = new QRegExpValidator{QRegExp{hexRegex}, this};
    m_lineEdit->setValidator(validator);
    
    this->connect(m_button, &ColorButton::pressed, this, &ColorEditor::openColorPicker);
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &ColorEditor::parseColor);

    m_propertyChangedConnection = m_property->valueChanged.connect(
        [this]()
        {
            m_button->blockSignals(true);
            m_lineEdit->blockSignals(true);

            Color color = m_property->toColor();
            QColor qcolor = toQColor(color);
            m_button->setColor(qcolor);
            m_lineEdit->setText(QString::fromStdString(color.toString(m_alpha)));

            m_button->blockSignals(false);
            m_lineEdit->blockSignals(false);
        });
}

ColorEditor::~ColorEditor()
{
}
    
void ColorEditor::openColorPicker()
{
    auto options = m_alpha ? QColorDialog::ShowAlphaChannel : QColorDialog::ColorDialogOptions();
    
    auto qcolor = QColorDialog::getColor(
        qColor(),
        m_button,
        "Choose Color",
        options);
        
    if (qcolor.isValid())
        this->setQColor(qcolor);
}

void ColorEditor::parseColor()
{
    QString text = m_lineEdit->text();
    bool ok;
    auto color = Color::fromString(text.toStdString(), &ok);
    assert(ok);
    this->setColor(color);
}
    
QColor ColorEditor::qColor() const
{
    return toQColor(m_property->toColor());
}

void ColorEditor::setQColor(const QColor & qcolor)
{
    Color color = toColor(qcolor);
    m_property->fromColor(color);
    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(color.toString(m_alpha)));
}

void ColorEditor::setColor(const Color & color)
{
    QColor qcolor = toQColor(color);
    m_property->fromColor(color);
    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(color.toString(m_alpha)));
}

} // namespace propertyguizeug
