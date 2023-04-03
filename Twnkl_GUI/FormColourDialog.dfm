object frmColourDialog: TfrmColourDialog
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'frmColourDialog'
  ClientHeight = 223
  ClientWidth = 521
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object sShapeColour: TShape
    Left = 8
    Top = 8
    Width = 145
    Height = 129
  end
  object Bevel1: TBevel
    Left = 8
    Top = 176
    Width = 505
    Height = 9
    Shape = bsTopLine
  end
  object Label1: TLabel
    Left = 170
    Top = 40
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 170
    Top = 79
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object Label3: TLabel
    Left = 170
    Top = 118
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object tbRed: TTrackBar
    Left = 207
    Top = 40
    Width = 306
    Height = 33
    Max = 255
    TabOrder = 0
    OnChange = tbRedChange
  end
  object tbGreen: TTrackBar
    Left = 207
    Top = 79
    Width = 306
    Height = 33
    Max = 255
    TabOrder = 1
    OnChange = tbRedChange
  end
  object tbBlue: TTrackBar
    Left = 207
    Top = 118
    Width = 306
    Height = 33
    Max = 255
    TabOrder = 2
    OnChange = tbRedChange
  end
  object BitBtn1: TBitBtn
    Left = 357
    Top = 191
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 3
  end
  object BitBtn2: TBitBtn
    Left = 438
    Top = 191
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 4
  end
end
