#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>
#include "Effects.h"

namespace Ui {
  class SettingsForm;
}

class SettingsForm : public QDialog
{
  Q_OBJECT

public:
  explicit SettingsForm(QWidget *parent = nullptr);
  ~SettingsForm();

  const std::tuple<bool,QString> matrixEffectSettings() const;

private slots:
  void on_checkBoxMatrix_stateChanged(int arg1);
  void on_comboBoxColorMatrix_currentTextChanged(const QString &arg1);

private:
  Ui::SettingsForm *ui;
  std::tuple<bool,QString> m_matrixSettings;
signals:
  void effectEnabled(Effects e);
  void colorChanged(Effects e ,const QString& colorTag);
};

#endif // SETTINGSFORM_H
