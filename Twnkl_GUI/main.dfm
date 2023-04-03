object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 610
  ClientWidth = 1150
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1150
    Height = 41
    Align = alTop
    TabOrder = 0
    object bOpenSource: TBitBtn
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Open'
      TabOrder = 0
      OnClick = bOpenSceneClick
    end
    object bRender: TBitBtn
      Left = 89
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Render'
      TabOrder = 1
      OnClick = bRenderClick
    end
    object BitBtn1: TBitBtn
      Left = 170
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 2
      OnClick = BitBtn1Click
    end
    object cbResizeToDisplay: TCheckBox
      Left = 251
      Top = 12
      Width = 102
      Height = 17
      Caption = 'Resize to display'
      TabOrder = 3
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 281
    Height = 550
    Align = alLeft
    TabOrder = 1
    object tvObjects: TTreeView
      Left = 8
      Top = 6
      Width = 265
      Height = 171
      HideSelection = False
      Indent = 19
      TabOrder = 0
      OnClick = tvObjectsClick
    end
    object PageControl1: TPageControl
      Left = 8
      Top = 192
      Width = 268
      Height = 353
      ActivePage = TabSheet3
      TabOrder = 1
      object tsCamera: TTabSheet
        Caption = 'Camera'
        ImageIndex = 2
      end
      object tsLight: TTabSheet
        Caption = 'Light'
        ImageIndex = 3
      end
      object TabSheet3: TTabSheet
        Caption = 'Transforms'
        ImageIndex = 1
        object lbObjectTransforms: TListBox
          Left = 3
          Top = 3
          Width = 246
          Height = 97
          ItemHeight = 13
          TabOrder = 0
          OnClick = lbObjectTransformsClick
        end
        object pOTAngle: TPanel
          Left = 3
          Top = 106
          Width = 246
          Height = 31
          TabOrder = 1
          object Label11: TLabel
            Left = 31
            Top = 8
            Width = 27
            Height = 13
            Caption = 'Angle'
          end
          object Label15: TLabel
            Left = 155
            Top = 8
            Width = 35
            Height = 13
            Caption = 'radians'
          end
          object eOTAngle: TEdit
            Left = 93
            Top = 0
            Width = 56
            Height = 21
            TabOrder = 0
            Text = '.'
            OnExit = eOTAngleExit
          end
        end
        object pOTXYZ: TPanel
          Left = 3
          Top = 143
          Width = 246
          Height = 98
          TabOrder = 2
          object Label12: TLabel
            Left = 31
            Top = 11
            Width = 6
            Height = 13
            Caption = 'X'
          end
          object Label14: TLabel
            Left = 31
            Top = 64
            Width = 6
            Height = 13
            Caption = 'Z'
          end
          object Label13: TLabel
            Left = 31
            Top = 37
            Width = 6
            Height = 13
            Caption = 'Y'
          end
          object eOTX: TEdit
            Left = 93
            Top = 7
            Width = 56
            Height = 21
            TabOrder = 0
            Text = '.'
            OnExit = eOTXExit
          end
          object eOTY: TEdit
            Left = 93
            Top = 34
            Width = 56
            Height = 21
            TabOrder = 1
            Text = '.'
            OnExit = eOTXExit
          end
          object eOTZ: TEdit
            Left = 93
            Top = 61
            Width = 56
            Height = 21
            TabOrder = 2
            Text = '.'
            OnExit = eOTXExit
          end
        end
      end
      object tsMaterial: TTabSheet
        Caption = 'Material'
        object PageControl2: TPageControl
          Left = 0
          Top = 0
          Width = 260
          Height = 325
          ActivePage = tsBasic
          Align = alClient
          TabOrder = 0
          object tsBasic: TTabSheet
            Caption = 'Basic'
            object Label7: TLabel
              Left = 4
              Top = 242
              Width = 66
              Height = 13
              BiDiMode = bdLeftToRight
              Caption = 'Transparency'
              ParentBiDiMode = False
            end
            object Label6: TLabel
              Left = 4
              Top = 213
              Width = 41
              Height = 13
              Caption = 'Specular'
            end
            object Label5: TLabel
              Left = 4
              Top = 184
              Width = 44
              Height = 13
              Caption = 'Shininess'
            end
            object Label4: TLabel
              Left = 4
              Top = 152
              Width = 17
              Height = 13
              Caption = 'IoR'
            end
            object Label3: TLabel
              Left = 4
              Top = 120
              Width = 48
              Height = 13
              Caption = 'Reflective'
            end
            object Label2: TLabel
              Left = 4
              Top = 88
              Width = 34
              Height = 13
              Caption = 'Diffuse'
            end
            object Label1: TLabel
              Left = 4
              Top = 56
              Width = 46
              Height = 13
              Caption = 'Ambience'
            end
            object sMaterialColour: TShape
              Left = 79
              Top = 11
              Width = 50
              Height = 22
              OnMouseDown = sMaterialColourMouseDown
            end
            object Label8: TLabel
              Left = 3
              Top = 11
              Width = 37
              Height = 13
              Caption = 'Surface'
            end
            object lSurfaceColourWarning: TLabel
              Left = 135
              Top = 15
              Width = 96
              Height = 13
              Caption = 'Pattern sets colours'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clMaroon
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              Visible = False
            end
            object tbTransparency: TTrackBar
              Tag = 6
              Left = 73
              Top = 242
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 0
              OnExit = tbAmbientExit
            end
            object tbSpecular: TTrackBar
              Tag = 5
              Left = 73
              Top = 211
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 1
              OnExit = tbAmbientExit
            end
            object tbShininess: TTrackBar
              Tag = 4
              Left = 73
              Top = 180
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 2
              OnExit = tbAmbientExit
            end
            object tbIoR: TTrackBar
              Tag = 3
              Left = 73
              Top = 148
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 3
              OnExit = tbAmbientExit
            end
            object tbReflectivity: TTrackBar
              Tag = 2
              Left = 73
              Top = 120
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 4
              OnExit = tbAmbientExit
            end
            object tbDiffuse: TTrackBar
              Tag = 1
              Left = 73
              Top = 88
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 5
              OnExit = tbAmbientExit
            end
            object tbAmbient: TTrackBar
              Left = 73
              Top = 56
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 6
              OnExit = tbAmbientExit
            end
          end
          object tsPattern: TTabSheet
            Caption = 'Pattern'
            ImageIndex = 1
            object Label9: TLabel
              Left = 3
              Top = 11
              Width = 48
              Height = 13
              Caption = 'Colour #1'
            end
            object sPatternColour1: TShape
              Left = 79
              Top = 11
              Width = 98
              Height = 22
              OnMouseDown = sPatternColour1MouseDown
            end
            object Label10: TLabel
              Left = 3
              Top = 39
              Width = 48
              Height = 13
              Caption = 'Colour #2'
            end
            object sPatternColour2: TShape
              Tag = 1
              Left = 79
              Top = 39
              Width = 98
              Height = 22
              OnMouseDown = sPatternColour1MouseDown
            end
          end
          object Transforms: TTabSheet
            Caption = 'Transforms'
            ImageIndex = 2
          end
        end
      end
    end
  end
  object Panel3: TPanel
    Left = 281
    Top = 41
    Width = 869
    Height = 550
    Align = alClient
    TabOrder = 2
    object PaintBox1: TPaintBox
      Left = 1
      Top = 1
      Width = 867
      Height = 548
      Align = alClient
      ExplicitLeft = -584
      ExplicitTop = 14
      ExplicitWidth = 825
      ExplicitHeight = 356
    end
  end
  object sbMain: TStatusBar
    Left = 0
    Top = 591
    Width = 1150
    Height = 19
    Panels = <>
    SimplePanel = True
  end
end
