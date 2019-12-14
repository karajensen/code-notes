/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT RENDER
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// QColor
// Uses typedef QRgb unsigned int
// 'F' uses float [0,1], otherwise int [0,255] or [0, 359] (hue)
// Comparison will also take into account last set color mode
QColor color(r, g, b, a) // int only
QColor color("red")
QColor color(Qt::GlobalColor::red)
QColor color(QRgb(0)) // Ignores alpha
color.name() // QString "#RRGGBB", same as color.name(QColor::NameFormat::HexRgb)
color.name(QColor::NameFormat::HexArgb) // QString "#AARRGGBB", Also can have QColor::HexRgb
color.alpha() / color.alphaF() / color.setAlpha(0) / color.setAlphaF(0)
color.red() / color.redF() / color.setRed(0) / color.setRedF(0)
color.blue() / color.blueF() / color.setBlue(0) / color.setBlueF(0)
color.green() / color.greenF() / color.setGreen(0) / color.setGreenF(0)
color.hue() / color.hueF() // HSV
color.saturation() / color.saturationF() // HSV
color.value() / color.valueF() // HSV
color.lightness() / color.lightnessF() // HSL
color.hslHue() / color.hslHueF()
color.hslSaturation() / color.hslSaturationF()
color.hsvHue() / color.hsvHueF()
color.hsvSaturation() / color.hsvSaturationF()
color.setHsl(h, s, l, a) / color.setHslF(h, s, l, a) // Alpha optional
color.setHsv(h, s, v, a) / color.setHsvF(h, s, v, a) // Alpha optional
color.setRgb(r, g, b, a) / color.setRgbF(r, g, b, a) // Alpha optional
color.setRgb(QRgb(0)) // Ignores alpha
color.setRgb(QRgb(0)) // Keeps alpha component
color.lighter(factor) // Returns QColor lighter by int factor, default is 150
color.darker(factor) // Returns QColor darker by int factor, default is 200
color.rgb() // Returns unsigned int, use for comparison as QColor comparison also uses color mode
color.rgba() // Returns unsigned int, use for comparison as QColor comparison also uses color mode
color.toCmyk() // Returns QColor with color mode CMYK
color.toHsl() // Returns QColor with color mode HSL
color.toHsv() // Returns QColor with color mode HSV
color.toRgb() // Returns QColor with color mode RGB
QColor::colorNames() // Returns QStringList with all valid color names (eg. "red")
QColor::fromCmyk(c, m, y, k, a) // Alpha optional
QColor::fromCmykF c, m, y, k, a) // Alpha optional
QColor::fromHsl(h, s, l, a) // Alpha optional
QColor::fromHslF(h, s, l, a) // Alpha optional
QColor::fromHsv(h, s, v, a) // Alpha optional
QColor::fromHsvF(h, s, v, a) // Alpha optional
QColor::fromRgb(QRgb(0)) // Ignores alpha
QColor::fromRgb(r, g, b, a) // Alpha optional
QColor::fromRgbF(r, g, b, a) // Alpha optional
QColor::fromRgba(QRgb(0)) // Keeps alpha component

// QImage
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QPAINTER RENDERING
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  
  
