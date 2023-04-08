object frmAddObject: TfrmAddObject
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Add Object'
  ClientHeight = 439
  ClientWidth = 469
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 168
    Top = 8
    Width = 9
    Height = 385
    Shape = bsLeftLine
  end
  object Bevel2: TBevel
    Left = 6
    Top = 399
    Width = 455
    Height = 2
    Shape = bsTopLine
  end
  object pPattern: TPanel
    Left = 183
    Top = 56
    Width = 280
    Height = 337
    TabOrder = 5
    Visible = False
    object lPatternColour1: TLabel
      Left = 11
      Top = 14
      Width = 48
      Height = 13
      Caption = 'Colour #1'
    end
    object sPatternColour1: TShape
      Left = 81
      Top = 11
      Width = 56
      Height = 22
      Brush.Color = clSilver
      OnMouseDown = sPatternColour1MouseDown
    end
    object sPatternColour2: TShape
      Tag = 1
      Left = 81
      Top = 39
      Width = 56
      Height = 22
      Brush.Color = clGray
      OnMouseDown = sPatternColour1MouseDown
    end
    object lPatternColour2: TLabel
      Left = 11
      Top = 42
      Width = 48
      Height = 13
      Caption = 'Colour #2'
    end
    object lPWidth: TLabel
      Left = 144
      Top = 14
      Width = 28
      Height = 13
      Caption = 'Width'
    end
    object lPHeight: TLabel
      Left = 144
      Top = 41
      Width = 31
      Height = 13
      Caption = 'Height'
    end
    object lPScale: TLabel
      Left = 11
      Top = 90
      Width = 25
      Height = 13
      Caption = 'Scale'
    end
    object lPPhase: TLabel
      Left = 11
      Top = 117
      Width = 29
      Height = 13
      Caption = 'Phase'
    end
    object lPFrequency: TLabel
      Left = 11
      Top = 144
      Width = 51
      Height = 13
      Caption = 'Frequency'
    end
    object lPLacunarity: TLabel
      Left = 11
      Top = 198
      Width = 50
      Height = 13
      Caption = 'Lacunarity'
    end
    object lPPersistence: TLabel
      Left = 11
      Top = 225
      Width = 55
      Height = 13
      Caption = 'Persistence'
    end
    object lPAmplitude: TLabel
      Left = 11
      Top = 171
      Width = 47
      Height = 13
      Caption = 'Amplitude'
    end
    object lTexture: TLabel
      Left = 11
      Top = 305
      Width = 38
      Height = 13
      Caption = 'Texture'
    end
    object lTexturePath: TLabel
      Left = 81
      Top = 305
      Width = 12
      Height = 13
      Caption = '...'
    end
    object ePWidth: TEdit
      Left = 201
      Top = 11
      Width = 56
      Height = 21
      TabOrder = 0
      Text = '.'
    end
    object ePHeight: TEdit
      Left = 201
      Top = 38
      Width = 56
      Height = 21
      TabOrder = 1
      Text = '.'
    end
    object ePScale: TEdit
      Left = 81
      Top = 87
      Width = 56
      Height = 21
      TabOrder = 2
      Text = '.'
    end
    object ePPhase: TEdit
      Left = 81
      Top = 114
      Width = 56
      Height = 21
      TabOrder = 3
      Text = '.'
    end
    object ePFrequency: TEdit
      Left = 81
      Top = 141
      Width = 56
      Height = 21
      TabOrder = 4
      Text = '.'
    end
    object ePAmplitude: TEdit
      Left = 81
      Top = 168
      Width = 56
      Height = 21
      TabOrder = 5
      Text = '.'
    end
    object ePLacunarity: TEdit
      Left = 81
      Top = 195
      Width = 56
      Height = 21
      TabOrder = 6
      Text = '.'
    end
    object ePPersistence: TEdit
      Left = 81
      Top = 222
      Width = 56
      Height = 21
      TabOrder = 7
      Text = '.'
    end
    object cbPSimple: TCheckBox
      Left = 143
      Top = 89
      Width = 97
      Height = 17
      Caption = 'Simple'
      TabOrder = 8
    end
    object bOpenTexture: TBitBtn
      Left = 245
      Top = 304
      Width = 28
      Height = 25
      TabOrder = 9
      OnClick = bOKClick
    end
  end
  object cbPrimitive: TComboBox
    Left = 8
    Top = 16
    Width = 145
    Height = 21
    Style = csDropDownList
    TabOrder = 0
    OnChange = cbPrimitiveChange
    Items.Strings = (
      'Cone'
      'Cube'
      'Cylinder'
      'Model'
      'Plane'
      'Sphere')
  end
  object bOK: TBitBtn
    Left = 305
    Top = 407
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
    OnClick = bOKClick
  end
  object bCancel: TBitBtn
    Left = 386
    Top = 407
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object eName: TEdit
    Left = 8
    Top = 56
    Width = 145
    Height = 21
    TabOrder = 3
    OnExit = eNameExit
  end
  object cbPattern: TComboBox
    Left = 183
    Top = 16
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 4
    Text = 'None'
    OnChange = cbPatternChange
    Items.Strings = (
      'None'
      'Checker'
      'Fractal'
      'Gradient'
      'Gradient II'
      'Perlin'
      'Perlin II'
      'Perlin III'
      'Ring'
      'Simplex'
      'Stripey'
      'Texture')
  end
end
