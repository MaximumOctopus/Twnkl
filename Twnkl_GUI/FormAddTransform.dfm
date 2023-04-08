object frmAddTransform: TfrmAddTransform
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Add Transform'
  ClientHeight = 221
  ClientWidth = 253
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object pAngle: TPanel
    Left = 1
    Top = 35
    Width = 246
    Height = 38
    TabOrder = 0
    Visible = False
    object Label16: TLabel
      Left = 31
      Top = 9
      Width = 27
      Height = 13
      Caption = 'Angle'
    end
    object Label17: TLabel
      Left = 156
      Top = 9
      Width = 35
      Height = 13
      Caption = 'radians'
    end
    object eAngle: TEdit
      Left = 93
      Top = 6
      Width = 56
      Height = 21
      TabOrder = 0
      Text = '0'
      OnExit = eAngleExit
    end
  end
  object pXYZ: TPanel
    Left = 1
    Top = 79
    Width = 246
    Height = 98
    TabOrder = 1
    object Label18: TLabel
      Left = 31
      Top = 10
      Width = 6
      Height = 13
      Caption = 'X'
    end
    object Label19: TLabel
      Left = 31
      Top = 64
      Width = 6
      Height = 13
      Caption = 'Z'
    end
    object Label20: TLabel
      Left = 31
      Top = 37
      Width = 6
      Height = 13
      Caption = 'Y'
    end
    object eX: TEdit
      Left = 93
      Top = 7
      Width = 56
      Height = 21
      TabOrder = 0
      Text = '0'
      OnExit = eXExit
    end
    object eY: TEdit
      Left = 93
      Top = 34
      Width = 56
      Height = 21
      TabOrder = 1
      Text = '0'
      OnExit = eYExit
    end
    object eZ: TEdit
      Left = 93
      Top = 61
      Width = 56
      Height = 21
      TabOrder = 2
      Text = '0'
      OnExit = eZExit
    end
  end
  object BitBtn1: TBitBtn
    Left = 91
    Top = 191
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 2
  end
  object BitBtn2: TBitBtn
    Left = 172
    Top = 191
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
  object cbTransform: TComboBox
    Left = 94
    Top = 8
    Width = 116
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 4
    Text = 'Scale'
    OnChange = cbTransformChange
    Items.Strings = (
      'Scale'
      'Translate'
      'Rotate X'
      'Rotate Y'
      'Rotate Z')
  end
end
