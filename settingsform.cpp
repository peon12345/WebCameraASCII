#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SettingsForm)
{
  ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
  delete ui;
}

const std::tuple<bool, QString> SettingsForm::matrixEffectSettings() const
{
  return m_matrixSettings;
}

void SettingsForm::on_checkBoxMatrix_stateChanged(int arg1)
{
    std::get<0>(m_matrixSettings) = arg1;
    emit effectEnabled(Effects::MATRIX);
}


void SettingsForm::on_comboBoxColorMatrix_currentTextChanged(const QString &arg1)
{
    std::get<1>(m_matrixSettings) = arg1;
    emit colorChanged(Effects::MATRIX,arg1);
}
