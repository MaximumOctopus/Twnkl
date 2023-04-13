object frmMain: TfrmMain
  Left = 4
  Top = 4
  Caption = 'frmMain'
  ClientHeight = 733
  ClientWidth = 1189
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1189
    Height = 41
    Align = alTop
    TabOrder = 0
    object Bevel1: TBevel
      Left = 88
      Top = 8
      Width = 10
      Height = 25
      Shape = bsLeftLine
    end
    object Bevel2: TBevel
      Left = 255
      Top = 8
      Width = 10
      Height = 25
      Shape = bsLeftLine
    end
    object Bevel3: TBevel
      Left = 423
      Top = 8
      Width = 10
      Height = 25
      Shape = bsLeftLine
    end
    object bOpenScene: TBitBtn
      Left = 94
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Open'
      TabOrder = 0
      OnClick = bOpenSceneClick
    end
    object bRender: TBitBtn
      Left = 262
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Render'
      TabOrder = 1
      OnClick = bRenderClick
    end
    object cbResizeToDisplay: TCheckBox
      Left = 433
      Top = 12
      Width = 102
      Height = 17
      Caption = 'Resize to display'
      TabOrder = 2
    end
    object bSaveScene: TBitBtn
      Left = 175
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Save'
      TabOrder = 3
      OnClick = bSaveSceneClick
    end
    object bNew: TBitBtn
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'New'
      TabOrder = 4
      OnClick = bNewClick
    end
    object bSaveImage: TBitBtn
      Left = 343
      Top = 8
      Width = 74
      Height = 25
      Caption = 'Export'
      TabOrder = 5
      OnClick = bSaveImageClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 281
    Height = 673
    Align = alLeft
    TabOrder = 1
    DesignSize = (
      281
      673)
    object sbAddObject: TSpeedButton
      Left = 8
      Top = 6
      Width = 23
      Height = 22
      Caption = '+'
      OnClick = sbAddObjectClick
    end
    object sbDeleteObject: TSpeedButton
      Left = 8
      Top = 34
      Width = 23
      Height = 22
      Caption = '-'
      OnClick = sbDeleteObjectClick
    end
    object tvObjects: TTreeView
      Left = 39
      Top = 6
      Width = 236
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
      Height = 476
      ActivePage = tsCamera
      Anchors = [akLeft, akTop, akBottom]
      TabOrder = 1
      object tsCamera: TTabSheet
        Caption = 'Camera'
        ImageIndex = 2
        object Label32: TLabel
          Left = 27
          Top = 11
          Width = 18
          Height = 13
          Caption = 'FoV'
        end
        object Label33: TLabel
          Left = 27
          Top = 150
          Width = 24
          Height = 13
          Caption = 'From'
        end
        object Label34: TLabel
          Left = 27
          Top = 177
          Width = 12
          Height = 13
          Caption = 'To'
        end
        object Label35: TLabel
          Left = 27
          Top = 204
          Width = 13
          Height = 13
          Caption = 'Up'
        end
        object Label36: TLabel
          Left = 113
          Top = 128
          Width = 6
          Height = 13
          Caption = 'X'
        end
        object Label37: TLabel
          Left = 172
          Top = 128
          Width = 6
          Height = 13
          Caption = 'Y'
        end
        object Label38: TLabel
          Left = 225
          Top = 128
          Width = 6
          Height = 13
          Caption = 'Z'
        end
        object Label26: TLabel
          Left = 27
          Top = 51
          Width = 28
          Height = 13
          Caption = 'Width'
        end
        object Label27: TLabel
          Left = 27
          Top = 78
          Width = 31
          Height = 13
          Caption = 'Height'
        end
        object Label28: TLabel
          Left = 27
          Top = 254
          Width = 61
          Height = 13
          Caption = 'Supersample'
        end
        object eCFoV: TEdit
          Left = 101
          Top = 8
          Width = 56
          Height = 21
          TabOrder = 0
          Text = '1.152'
          OnExit = eCFoVExit
        end
        object eCFromX: TEdit
          Left = 101
          Top = 147
          Width = 49
          Height = 21
          TabOrder = 1
          Text = '.'
          OnExit = eCFromXExit
        end
        object eCFromY: TEdit
          Left = 156
          Top = 147
          Width = 47
          Height = 21
          TabOrder = 2
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCFromZ: TEdit
          Left = 209
          Top = 147
          Width = 47
          Height = 21
          TabOrder = 3
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCToX: TEdit
          Left = 101
          Top = 174
          Width = 49
          Height = 21
          TabOrder = 4
          Text = '.'
          OnExit = eCToXExit
        end
        object eCToY: TEdit
          Left = 156
          Top = 174
          Width = 47
          Height = 21
          TabOrder = 5
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCToZ: TEdit
          Left = 209
          Top = 174
          Width = 48
          Height = 21
          TabOrder = 6
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCUpX: TEdit
          Left = 101
          Top = 201
          Width = 49
          Height = 21
          TabOrder = 7
          Text = '.'
          OnExit = eCUpXExit
        end
        object eCUpY: TEdit
          Left = 156
          Top = 201
          Width = 47
          Height = 21
          TabOrder = 8
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCUpZ: TEdit
          Left = 209
          Top = 201
          Width = 48
          Height = 21
          TabOrder = 9
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCWidth: TEdit
          Left = 101
          Top = 48
          Width = 56
          Height = 21
          TabOrder = 10
          Text = '1'
          OnExit = eCWidthExit
        end
        object eCHeight: TEdit
          Left = 101
          Top = 75
          Width = 56
          Height = 21
          TabOrder = 11
          Text = '1'
          OnExit = eCWidthExit
        end
        object eCSuperSamples: TEdit
          Left = 101
          Top = 251
          Width = 56
          Height = 21
          TabOrder = 12
          Text = '0'
          OnExit = eCWidthExit
        end
      end
      object tsLight: TTabSheet
        Caption = 'Light'
        ImageIndex = 3
        object Label21: TLabel
          Left = 27
          Top = 14
          Width = 31
          Height = 13
          Caption = 'Colour'
        end
        object sLightIntensity: TShape
          Left = 101
          Top = 11
          Width = 50
          Height = 22
          OnMouseDown = sLightIntensityMouseDown
        end
        object Label10: TLabel
          Left = 27
          Top = 85
          Width = 46
          Height = 13
          Caption = 'Position X'
        end
        object Label24: TLabel
          Left = 27
          Top = 112
          Width = 46
          Height = 13
          Caption = 'Position Y'
        end
        object Label25: TLabel
          Left = 27
          Top = 139
          Width = 46
          Height = 13
          Caption = 'Position Z'
        end
        object eLPositionX: TEdit
          Left = 101
          Top = 82
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnExit = eLPositionXExit
        end
        object eLPositionY: TEdit
          Left = 101
          Top = 109
          Width = 49
          Height = 21
          TabOrder = 1
          Text = '0'
          OnExit = eLPositionXExit
        end
        object eLPositionZ: TEdit
          Left = 101
          Top = 136
          Width = 49
          Height = 21
          TabOrder = 2
          Text = '0'
          OnExit = eLPositionXExit
        end
      end
      object tsObject: TTabSheet
        Caption = 'Object'
        ImageIndex = 4
        object lOMinimum: TLabel
          Left = 27
          Top = 58
          Width = 40
          Height = 13
          Caption = 'Minimum'
        end
        object lOMaximum: TLabel
          Left = 27
          Top = 85
          Width = 44
          Height = 13
          Caption = 'Maximum'
        end
        object Label9: TLabel
          Left = 27
          Top = 12
          Width = 40
          Height = 13
          Caption = 'Primitive'
        end
        object lOPrimitive: TLabel
          Left = 101
          Top = 12
          Width = 15
          Height = 13
          Caption = '.....'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lOObjectFileName: TLabel
          Left = 27
          Top = 205
          Width = 32
          Height = 13
          Caption = 'Object'
        end
        object eOObjectFileName: TLabel
          Left = 101
          Top = 205
          Width = 12
          Height = 13
          Caption = '...'
        end
        object eOMinimum: TEdit
          Left = 101
          Top = 55
          Width = 56
          Height = 21
          TabOrder = 0
          Text = '1'
        end
        object eOMaximum: TEdit
          Left = 101
          Top = 82
          Width = 56
          Height = 21
          TabOrder = 1
          Text = '1'
        end
        object cbOClosed: TCheckBox
          Left = 27
          Top = 125
          Width = 97
          Height = 17
          Caption = 'Closed'
          TabOrder = 2
        end
      end
      object tsTransforms: TTabSheet
        Caption = 'Transforms'
        ImageIndex = 1
        object sbAddTransform: TSpeedButton
          Left = 5
          Top = 3
          Width = 23
          Height = 22
          Caption = '+'
          OnClick = sbAddTransformClick
        end
        object sbDeleteTransform: TSpeedButton
          Left = 5
          Top = 31
          Width = 23
          Height = 22
          Caption = '-'
          OnClick = sbDeleteTransformClick
        end
        object lbObjectTransforms: TListBox
          Left = 34
          Top = 3
          Width = 215
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
            Top = 3
            Width = 27
            Height = 13
            Caption = 'Angle'
          end
          object Label15: TLabel
            Left = 155
            Top = 3
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
            Top = 10
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
          Height = 448
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
              Left = 4
              Top = 14
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
            object tbReflectivity: TTrackBar
              Tag = 2
              Left = 73
              Top = 120
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 3
              OnExit = tbAmbientExit
            end
            object tbDiffuse: TTrackBar
              Tag = 1
              Left = 73
              Top = 88
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 4
              OnExit = tbAmbientExit
            end
            object tbAmbient: TTrackBar
              Left = 73
              Top = 56
              Width = 176
              Height = 33
              Max = 100
              TabOrder = 5
              OnExit = tbAmbientExit
            end
            object tbIoR: TTrackBar
              Tag = 3
              Left = 73
              Top = 148
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
            object lPatternColour1: TLabel
              Left = 3
              Top = 46
              Width = 48
              Height = 13
              Caption = 'Colour #1'
            end
            object sPatternColour1: TShape
              Left = 73
              Top = 43
              Width = 56
              Height = 22
              OnMouseDown = sPatternColour1MouseDown
            end
            object lPatternColour2: TLabel
              Left = 3
              Top = 74
              Width = 48
              Height = 13
              Caption = 'Colour #2'
            end
            object sPatternColour2: TShape
              Tag = 1
              Left = 73
              Top = 71
              Width = 56
              Height = 22
              OnMouseDown = sPatternColour1MouseDown
            end
            object Label22: TLabel
              Left = 3
              Top = 323
              Width = 37
              Height = 13
              Caption = 'Change'
            end
            object Label23: TLabel
              Left = 3
              Top = 12
              Width = 32
              Height = 13
              Caption = 'Design'
            end
            object lPatternDesign: TLabel
              Left = 73
              Top = 12
              Width = 15
              Height = 13
              Caption = '.....'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object sbPatternChange: TSpeedButton
              Left = 216
              Top = 318
              Width = 23
              Height = 22
              OnClick = sbPatternChangeClick
            end
            object lPScale: TLabel
              Left = 3
              Top = 122
              Width = 25
              Height = 13
              Caption = 'Scale'
            end
            object lPPhase: TLabel
              Left = 3
              Top = 149
              Width = 29
              Height = 13
              Caption = 'Phase'
            end
            object lPAmplitude: TLabel
              Left = 3
              Top = 203
              Width = 47
              Height = 13
              Caption = 'Amplitude'
            end
            object lPFrequency: TLabel
              Left = 3
              Top = 176
              Width = 51
              Height = 13
              Caption = 'Frequency'
            end
            object lPPersistence: TLabel
              Left = 3
              Top = 257
              Width = 55
              Height = 13
              Caption = 'Persistence'
            end
            object lPLacunarity: TLabel
              Left = 3
              Top = 230
              Width = 50
              Height = 13
              Caption = 'Lacunarity'
            end
            object lPHeight: TLabel
              Left = 136
              Top = 73
              Width = 31
              Height = 13
              Caption = 'Height'
            end
            object lPWidth: TLabel
              Left = 136
              Top = 46
              Width = 28
              Height = 13
              Caption = 'Width'
            end
            object lTexture: TLabel
              Left = 3
              Top = 289
              Width = 38
              Height = 13
              Caption = 'Texture'
            end
            object lTexturePath: TLabel
              Left = 73
              Top = 289
              Width = 12
              Height = 13
              Caption = '...'
            end
            object cbPatternChangeTo: TComboBox
              Left = 73
              Top = 319
              Width = 137
              Height = 21
              Style = csDropDownList
              ItemIndex = 0
              TabOrder = 0
              Text = 'None'
              OnChange = cbPatternChangeToChange
              Items.Strings = (
                'None'
                'Checkerboard'
                'Fractal'
                'Gradient'
                'Gradient 2'
                'Perlin 1'
                'Perlin 2'
                'Perlin 3'
                'Ring'
                'Simplex'
                'Stripey'
                'Texture')
            end
            object ePScale: TEdit
              Left = 73
              Top = 119
              Width = 56
              Height = 21
              TabOrder = 1
              Text = '1'
              OnExit = ePScaleExit
            end
            object ePPhase: TEdit
              Left = 73
              Top = 146
              Width = 56
              Height = 21
              TabOrder = 2
              Text = '1'
              OnExit = ePPhaseExit
            end
            object ePFrequency: TEdit
              Left = 73
              Top = 173
              Width = 56
              Height = 21
              TabOrder = 3
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePAmplitude: TEdit
              Left = 73
              Top = 200
              Width = 56
              Height = 21
              TabOrder = 4
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePLacunarity: TEdit
              Left = 73
              Top = 227
              Width = 56
              Height = 21
              TabOrder = 5
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePPersistence: TEdit
              Left = 73
              Top = 254
              Width = 56
              Height = 21
              TabOrder = 6
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePWidth: TEdit
              Left = 193
              Top = 43
              Width = 56
              Height = 21
              TabOrder = 7
              Text = '1'
              OnExit = ePWidthExit
            end
            object ePHeight: TEdit
              Left = 193
              Top = 70
              Width = 56
              Height = 21
              TabOrder = 8
              Text = '1'
              OnExit = ePWidthExit
            end
            object cbPSimple: TCheckBox
              Left = 152
              Top = 121
              Width = 97
              Height = 17
              Caption = 'Simple'
              TabOrder = 9
              OnClick = cbPSimpleClick
            end
            object bOpenTexture: TBitBtn
              Left = 216
              Top = 288
              Width = 28
              Height = 25
              TabOrder = 10
            end
            object bSelectNewTexture: TBitBtn
              Left = 216
              Top = 344
              Width = 23
              Height = 22
              TabOrder = 11
            end
            object eNewTexture: TEdit
              Left = 73
              Top = 346
              Width = 137
              Height = 21
              TabOrder = 12
              OnExit = ePFrequencyExit
            end
          end
          object tsMaterialTransforms: TTabSheet
            Caption = 'Transforms'
            ImageIndex = 2
            object sbAddMaterialTransform: TSpeedButton
              Left = 0
              Top = 3
              Width = 23
              Height = 22
              Caption = '+'
              OnClick = sbAddMaterialTransformClick
            end
            object sbDeleteMaterialTransform: TSpeedButton
              Left = 0
              Top = 31
              Width = 23
              Height = 22
              Caption = '-'
              OnClick = sbDeleteMaterialTransformClick
            end
            object SpeedButton1: TSpeedButton
              Left = 0
              Top = 78
              Width = 23
              Height = 22
            end
            object lbPatternTransforms: TListBox
              Left = 29
              Top = 3
              Width = 220
              Height = 97
              ItemHeight = 13
              TabOrder = 0
              OnClick = lbPatternTransformsClick
            end
            object pPTAngle: TPanel
              Left = 3
              Top = 106
              Width = 246
              Height = 31
              TabOrder = 1
              object Label16: TLabel
                Left = 31
                Top = 3
                Width = 27
                Height = 13
                Caption = 'Angle'
              end
              object Label17: TLabel
                Left = 155
                Top = 3
                Width = 35
                Height = 13
                Caption = 'radians'
              end
              object ePTAngle: TEdit
                Left = 93
                Top = 0
                Width = 56
                Height = 21
                TabOrder = 0
                Text = '.'
                OnExit = ePTAngleExit
              end
            end
            object pPTXYZ: TPanel
              Left = 3
              Top = 143
              Width = 246
              Height = 98
              TabOrder = 2
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
              object ePTX: TEdit
                Left = 93
                Top = 7
                Width = 56
                Height = 21
                TabOrder = 0
                Text = '.'
                OnExit = ePTXExit
              end
              object ePTY: TEdit
                Left = 93
                Top = 34
                Width = 56
                Height = 21
                TabOrder = 1
                Text = '.'
                OnExit = ePTXExit
              end
              object ePTZ: TEdit
                Left = 93
                Top = 61
                Width = 56
                Height = 21
                TabOrder = 2
                Text = '.'
                OnExit = ePTXExit
              end
            end
          end
        end
      end
    end
  end
  object pRender: TPanel
    Left = 281
    Top = 41
    Width = 908
    Height = 673
    Align = alClient
    TabOrder = 2
    object iRender: TImage
      Left = 4
      Top = 6
      Width = 105
      Height = 105
      AutoSize = True
    end
  end
  object sbMain: TStatusBar
    Left = 0
    Top = 714
    Width = 1189
    Height = 19
    Panels = <>
    SimplePanel = True
  end
end
