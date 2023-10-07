object frmMain: TfrmMain
  Left = 4
  Top = 4
  Caption = 'frmMain'
  ClientHeight = 733
  ClientWidth = 1145
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1145
    Height = 41
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 1141
    DesignSize = (
      1145
      41)
    object Bevel1: TBevel
      Left = 87
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
      Left = 422
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
      ImageIndex = 5
      Images = ImageList1
      TabOrder = 0
      OnClick = bOpenSceneClick
    end
    object bRender: TBitBtn
      Left = 262
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Render'
      ImageIndex = 2
      Images = ImageList1
      TabOrder = 1
      OnClick = bRenderClick
    end
    object bSaveScene: TBitBtn
      Left = 175
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Save'
      ImageIndex = 3
      Images = ImageList1
      TabOrder = 2
      OnClick = bSaveSceneClick
    end
    object bNew: TBitBtn
      Left = 6
      Top = 8
      Width = 75
      Height = 25
      Caption = 'New'
      ImageIndex = 4
      Images = ImageList1
      TabOrder = 3
      OnClick = bNewClick
    end
    object bSaveImage: TBitBtn
      Left = 343
      Top = 8
      Width = 74
      Height = 25
      Caption = 'Export'
      ImageIndex = 6
      Images = ImageList1
      TabOrder = 4
      OnClick = bSaveImageClick
    end
    object bAbout: TBitBtn
      Left = 1106
      Top = 8
      Width = 33
      Height = 25
      Anchors = [akTop, akRight]
      ImageIndex = 8
      Images = ImageList1
      TabOrder = 5
      OnClick = bAboutClick
      ExplicitLeft = 1102
    end
    object bDebug: TBitBtn
      Left = 1067
      Top = 8
      Width = 33
      Height = 25
      Anchors = [akTop, akRight]
      ImageIndex = 9
      Images = ImageList1
      TabOrder = 6
      OnClick = bDebugClick
      ExplicitLeft = 1063
    end
  end
  object Panel2: TPanel
    Left = 856
    Top = 41
    Width = 289
    Height = 673
    Align = alRight
    TabOrder = 1
    ExplicitLeft = 852
    ExplicitHeight = 672
    DesignSize = (
      289
      673)
    object sbAddObject: TSpeedButton
      Left = 6
      Top = 6
      Width = 23
      Height = 22
      ImageIndex = 0
      Images = ImageList1
      OnClick = sbAddObjectClick
    end
    object sbDeleteObject: TSpeedButton
      Left = 6
      Top = 30
      Width = 23
      Height = 22
      ImageIndex = 1
      Images = ImageList1
      Transparent = False
      OnClick = sbDeleteObjectClick
    end
    object sbCopyObject: TSpeedButton
      Left = 6
      Top = 142
      Width = 23
      Height = 22
      ImageIndex = 10
      Images = ImageList1
      Transparent = False
      OnClick = sbCopyObjectClick
    end
    object tvObjects: TTreeView
      Left = 35
      Top = 6
      Width = 246
      Height = 171
      HideSelection = False
      Indent = 19
      TabOrder = 0
      OnClick = tvObjectsClick
    end
    object pcMain: TPageControl
      Left = 6
      Top = 191
      Width = 275
      Height = 476
      ActivePage = tsCamera
      Anchors = [akLeft, akTop, akBottom]
      TabOrder = 1
      ExplicitHeight = 475
      object tsProject: TTabSheet
        Caption = 'Project'
        ImageIndex = 5
        object Label29: TLabel
          Left = 4
          Top = 11
          Width = 53
          Height = 13
          Caption = 'Description'
        end
        object Label30: TLabel
          Left = 4
          Top = 163
          Width = 33
          Height = 13
          Caption = 'Author'
        end
        object mDescription: TMemo
          Left = 4
          Top = 30
          Width = 261
          Height = 115
          TabOrder = 0
        end
        object eAuthor: TEdit
          Left = 4
          Top = 182
          Width = 261
          Height = 21
          TabOrder = 1
          OnExit = eCFoVExit
        end
      end
      object tsCamera: TTabSheet
        Caption = 'Camera'
        ImageIndex = 2
        object Label32: TLabel
          Left = 4
          Top = 11
          Width = 18
          Height = 13
          Caption = 'FoV'
        end
        object Label33: TLabel
          Left = 4
          Top = 150
          Width = 24
          Height = 13
          Caption = 'From'
        end
        object Label34: TLabel
          Left = 4
          Top = 177
          Width = 12
          Height = 13
          Caption = 'To'
        end
        object Label35: TLabel
          Left = 4
          Top = 204
          Width = 13
          Height = 13
          Caption = 'Up'
        end
        object Label36: TLabel
          Left = 89
          Top = 128
          Width = 7
          Height = 13
          Caption = 'X'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label37: TLabel
          Left = 148
          Top = 128
          Width = 7
          Height = 13
          Caption = 'Y'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label38: TLabel
          Left = 201
          Top = 128
          Width = 7
          Height = 13
          Caption = 'Z'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label26: TLabel
          Left = 4
          Top = 51
          Width = 59
          Height = 13
          Caption = 'Image width'
        end
        object Label27: TLabel
          Left = 4
          Top = 78
          Width = 63
          Height = 13
          Caption = 'Image height'
        end
        object Label28: TLabel
          Left = 4
          Top = 254
          Width = 61
          Height = 13
          Caption = 'Supersample'
        end
        object eCFoV: TEdit
          Left = 79
          Top = 8
          Width = 56
          Height = 21
          Alignment = taRightJustify
          TabOrder = 0
          Text = '1.152'
          OnExit = eCFoVExit
        end
        object eCFromX: TEdit
          Left = 79
          Top = 147
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 1
          Text = '.'
          OnExit = eCFromXExit
        end
        object eCFromY: TEdit
          Left = 134
          Top = 147
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 2
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCFromZ: TEdit
          Left = 189
          Top = 147
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 3
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCToX: TEdit
          Left = 79
          Top = 174
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 4
          Text = '.'
          OnExit = eCToXExit
        end
        object eCToY: TEdit
          Left = 134
          Top = 174
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 5
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCToZ: TEdit
          Left = 189
          Top = 174
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 6
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCUpX: TEdit
          Left = 79
          Top = 201
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 7
          Text = '.'
          OnExit = eCUpXExit
        end
        object eCUpY: TEdit
          Left = 134
          Top = 201
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 8
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCUpZ: TEdit
          Left = 189
          Top = 201
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 9
          Text = '.'
          OnExit = ePTAngleExit
        end
        object eCWidth: TEdit
          Left = 79
          Top = 48
          Width = 56
          Height = 21
          Alignment = taRightJustify
          TabOrder = 10
          Text = '1'
          OnExit = eCWidthExit
        end
        object eCHeight: TEdit
          Left = 79
          Top = 75
          Width = 56
          Height = 21
          Alignment = taRightJustify
          TabOrder = 11
          Text = '1'
          OnExit = eCWidthExit
        end
        object eCSuperSamples: TEdit
          Left = 79
          Top = 251
          Width = 56
          Height = 21
          Alignment = taRightJustify
          TabOrder = 12
          Text = '0'
          OnExit = eCWidthExit
        end
        object cbResizeToDisplay: TCheckBox
          Left = 147
          Top = 62
          Width = 101
          Height = 20
          Caption = 'Resize to display'
          TabOrder = 13
          OnClick = cbResizeToDisplayClick
        end
      end
      object tsLight: TTabSheet
        Caption = 'Light'
        ImageIndex = 3
        object Label21: TLabel
          Left = 4
          Top = 14
          Width = 31
          Height = 13
          Caption = 'Colour'
        end
        object sLightIntensity: TShape
          Left = 79
          Top = 11
          Width = 34
          Height = 22
          OnMouseDown = sLightIntensityMouseDown
        end
        object Label10: TLabel
          Left = 4
          Top = 85
          Width = 46
          Height = 13
          Caption = 'Position X'
        end
        object Label24: TLabel
          Left = 4
          Top = 112
          Width = 46
          Height = 13
          Caption = 'Position Y'
        end
        object Label25: TLabel
          Left = 4
          Top = 139
          Width = 46
          Height = 13
          Caption = 'Position Z'
        end
        object lLSamples: TLabel
          Left = 4
          Top = 181
          Width = 39
          Height = 13
          Caption = 'Samples'
        end
        object eLPositionX: TEdit
          Left = 79
          Top = 82
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 0
          Text = '0'
          OnExit = eLPositionXExit
        end
        object eLPositionY: TEdit
          Left = 79
          Top = 109
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 1
          Text = '0'
          OnExit = eLPositionXExit
        end
        object eLPositionZ: TEdit
          Left = 79
          Top = 136
          Width = 49
          Height = 21
          Alignment = taRightJustify
          TabOrder = 2
          Text = '0'
          OnExit = eLPositionXExit
        end
        object eLSamples: TEdit
          Left = 79
          Top = 178
          Width = 49
          Height = 21
          Alignment = taRightJustify
          NumbersOnly = True
          TabOrder = 3
          Text = '0'
          OnExit = eLSamplesExit
        end
      end
      object tsObject: TTabSheet
        Caption = 'Object'
        ImageIndex = 4
        object lOMinimum: TLabel
          Left = 4
          Top = 98
          Width = 40
          Height = 13
          Caption = 'Minimum'
        end
        object lOMaximum: TLabel
          Left = 4
          Top = 125
          Width = 44
          Height = 13
          Caption = 'Maximum'
        end
        object Label9: TLabel
          Left = 4
          Top = 52
          Width = 40
          Height = 13
          Caption = 'Primitive'
        end
        object lOPrimitive: TLabel
          Left = 79
          Top = 52
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
          Left = 4
          Top = 245
          Width = 32
          Height = 13
          Caption = 'Object'
        end
        object eOObjectFileName: TLabel
          Left = 79
          Top = 325
          Width = 12
          Height = 13
          Caption = '...'
        end
        object Name: TLabel
          Left = 4
          Top = 11
          Width = 27
          Height = 13
          Caption = 'Name'
        end
        object eOMinimum: TEdit
          Left = 79
          Top = 95
          Width = 56
          Height = 21
          Alignment = taRightJustify
          TabOrder = 0
          Text = '1'
        end
        object eOMaximum: TEdit
          Left = 79
          Top = 122
          Width = 56
          Height = 21
          Alignment = taRightJustify
          TabOrder = 1
          Text = '1'
        end
        object cbOClosed: TCheckBox
          Left = 4
          Top = 165
          Width = 62
          Height = 17
          Caption = 'Closed'
          TabOrder = 2
        end
        object eOName: TEdit
          Left = 79
          Top = 8
          Width = 178
          Height = 21
          TabOrder = 3
          OnExit = eONameExit
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
          ImageIndex = 0
          Images = ImageList1
          OnClick = sbAddTransformClick
        end
        object sbDeleteTransform: TSpeedButton
          Left = 5
          Top = 31
          Width = 23
          Height = 22
          ImageIndex = 1
          Images = ImageList1
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
            Top = 5
            Width = 56
            Height = 21
            Alignment = taRightJustify
            TabOrder = 0
            Text = '0'
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
            Alignment = taRightJustify
            TabOrder = 0
            Text = '0'
            OnExit = eOTXExit
          end
          object eOTY: TEdit
            Left = 93
            Top = 34
            Width = 56
            Height = 21
            Alignment = taRightJustify
            TabOrder = 1
            Text = '0'
            OnExit = eOTXExit
          end
          object eOTZ: TEdit
            Left = 93
            Top = 61
            Width = 56
            Height = 21
            Alignment = taRightJustify
            TabOrder = 2
            Text = '0'
            OnExit = eOTXExit
          end
        end
      end
      object tsMaterial: TTabSheet
        Caption = 'Material'
        object pcMaterial: TPageControl
          Left = 0
          Top = 0
          Width = 267
          Height = 448
          ActivePage = tsBasic
          Align = alClient
          TabOrder = 0
          OnChange = pcMaterialChange
          ExplicitHeight = 447
          object tsBasic: TTabSheet
            Caption = 'Basic'
            object Label7: TLabel
              Left = 3
              Top = 216
              Width = 66
              Height = 13
              BiDiMode = bdLeftToRight
              Caption = 'Transparency'
              ParentBiDiMode = False
            end
            object Label6: TLabel
              Left = 4
              Top = 184
              Width = 41
              Height = 13
              Caption = 'Specular'
            end
            object Label5: TLabel
              Left = 4
              Top = 152
              Width = 44
              Height = 13
              Caption = 'Shininess'
            end
            object Label4: TLabel
              Left = 3
              Top = 280
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
              Width = 34
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
              Left = 127
              Top = 14
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
            object lMBAmbience: TLabel
              Left = 223
              Top = 56
              Width = 16
              Height = 13
              Caption = '0.0'
            end
            object lMBDiffuse: TLabel
              Left = 223
              Top = 88
              Width = 16
              Height = 13
              Caption = '0.0'
            end
            object lMBReflectivity: TLabel
              Left = 223
              Top = 120
              Width = 16
              Height = 13
              Caption = '0.0'
            end
            object lMBShininess: TLabel
              Left = 223
              Top = 152
              Width = 16
              Height = 13
              Caption = '0.0'
            end
            object lMBSpecular: TLabel
              Left = 223
              Top = 184
              Width = 16
              Height = 13
              Caption = '0.0'
            end
            object lMBTransparency: TLabel
              Left = 223
              Top = 216
              Width = 16
              Height = 13
              BiDiMode = bdLeftToRight
              Caption = '0.0'
              ParentBiDiMode = False
            end
            object tbTransparency: TTrackBar
              Tag = 6
              Left = 73
              Top = 216
              Width = 150
              Height = 33
              Max = 100
              TabOrder = 0
              OnChange = tbAmbientChange
              OnExit = tbAmbientExit
            end
            object tbSpecular: TTrackBar
              Tag = 5
              Left = 73
              Top = 184
              Width = 150
              Height = 33
              Max = 100
              TabOrder = 1
              OnChange = tbAmbientChange
              OnExit = tbAmbientExit
            end
            object tbShininess: TTrackBar
              Tag = 4
              Left = 73
              Top = 152
              Width = 150
              Height = 33
              Max = 100
              TabOrder = 2
              OnChange = tbAmbientChange
              OnExit = tbAmbientExit
            end
            object tbReflectivity: TTrackBar
              Tag = 2
              Left = 73
              Top = 120
              Width = 150
              Height = 33
              Max = 100
              TabOrder = 3
              OnChange = tbAmbientChange
              OnExit = tbAmbientExit
            end
            object tbDiffuse: TTrackBar
              Tag = 1
              Left = 73
              Top = 88
              Width = 150
              Height = 33
              Max = 100
              TabOrder = 4
              OnChange = tbAmbientChange
              OnExit = tbAmbientExit
            end
            object tbAmbient: TTrackBar
              Left = 73
              Top = 56
              Width = 150
              Height = 33
              Max = 100
              TabOrder = 5
              OnChange = tbAmbientChange
              OnExit = tbAmbientExit
            end
            object bAddPattern: TBitBtn
              Left = 176
              Top = 392
              Width = 73
              Height = 25
              Caption = 'Add Pattern'
              TabOrder = 6
              Visible = False
              OnClick = bAddPatternClick
            end
            object cbIoRList: TComboBox
              Left = 79
              Top = 272
              Width = 155
              Height = 21
              Style = csDropDownList
              TabOrder = 7
              OnChange = cbIoRListChange
            end
            object eIoR: TEdit
              Left = 79
              Top = 299
              Width = 74
              Height = 21
              Alignment = taRightJustify
              TabOrder = 8
              Text = '1'
              OnExit = eIoRExit
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
              Width = 34
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
              Width = 34
              Height = 22
              OnMouseDown = sPatternColour1MouseDown
            end
            object Label22: TLabel
              Left = 3
              Top = 339
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
              Top = 334
              Width = 23
              Height = 22
              ImageIndex = 7
              Images = ImageList1
              OnClick = sbPatternChangeClick
            end
            object lPScale: TLabel
              Left = 3
              Top = 146
              Width = 25
              Height = 13
              Caption = 'Scale'
            end
            object lPPhase: TLabel
              Left = 3
              Top = 173
              Width = 29
              Height = 13
              Caption = 'Phase'
            end
            object lPAmplitude: TLabel
              Left = 3
              Top = 227
              Width = 47
              Height = 13
              Caption = 'Amplitude'
            end
            object lPFrequency: TLabel
              Left = 3
              Top = 200
              Width = 51
              Height = 13
              Caption = 'Frequency'
            end
            object lPPersistence: TLabel
              Left = 3
              Top = 281
              Width = 55
              Height = 13
              Caption = 'Persistence'
            end
            object lPLacunarity: TLabel
              Left = 3
              Top = 254
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
            object Bevel4: TBevel
              Left = 3
              Top = 314
              Width = 246
              Height = 2
              Shape = bsTopLine
            end
            object cbPatternChangeTo: TComboBox
              Left = 73
              Top = 335
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
              Top = 143
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 1
              Text = '1'
              OnExit = ePScaleExit
            end
            object ePPhase: TEdit
              Left = 73
              Top = 170
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 2
              Text = '1'
              OnExit = ePPhaseExit
            end
            object ePFrequency: TEdit
              Left = 73
              Top = 197
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 3
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePAmplitude: TEdit
              Left = 73
              Top = 224
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 4
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePLacunarity: TEdit
              Left = 73
              Top = 251
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 5
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePPersistence: TEdit
              Left = 73
              Top = 278
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 6
              Text = '1'
              OnExit = ePFrequencyExit
            end
            object ePWidth: TEdit
              Left = 193
              Top = 43
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 7
              Text = '1'
              OnExit = ePWidthExit
            end
            object ePHeight: TEdit
              Left = 193
              Top = 70
              Width = 56
              Height = 21
              Alignment = taRightJustify
              TabOrder = 8
              Text = '1'
              OnExit = ePWidthExit
            end
            object cbPSimple: TCheckBox
              Left = 152
              Top = 145
              Width = 97
              Height = 17
              Caption = 'Simple'
              TabOrder = 9
              OnClick = cbPSimpleClick
            end
            object bSelectNewTexture: TBitBtn
              Left = 216
              Top = 360
              Width = 23
              Height = 22
              ImageIndex = 5
              Images = ImageList1
              TabOrder = 10
              Visible = False
              OnClick = bSelectNewTextureClick
            end
            object eNewTexture: TEdit
              Left = 73
              Top = 362
              Width = 137
              Height = 21
              TabOrder = 11
              Visible = False
              OnExit = ePFrequencyExit
            end
            object cbPNoise: TCheckBox
              Left = 73
              Top = 113
              Width = 56
              Height = 17
              Caption = 'Noise'
              TabOrder = 12
              OnClick = cbPNoiseClick
            end
          end
          object tsTexture: TTabSheet
            Caption = 'Texture'
            ImageIndex = 3
            object iTexture: TImage
              Tag = -1
              Left = 1
              Top = 3
              Width = 256
              Height = 256
              Stretch = True
            end
            object lTextureDimensions: TLabel
              Left = 3
              Top = 265
              Width = 12
              Height = 13
              Caption = '...'
            end
            object lTexture: TLabel
              Left = 3
              Top = 321
              Width = 38
              Height = 13
              Caption = 'Texture'
            end
            object lTexturePath: TLabel
              Left = 73
              Top = 321
              Width = 137
              Height = 13
              AutoSize = False
              Caption = '...'
            end
            object Bevel5: TBevel
              Left = 3
              Top = 298
              Width = 246
              Height = 2
              Shape = bsTopLine
            end
            object bOpenTexture: TBitBtn
              Left = 233
              Top = 314
              Width = 23
              Height = 25
              ImageIndex = 5
              Images = ImageList1
              TabOrder = 0
              OnClick = bOpenTextureClick
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
              ImageIndex = 0
              Images = ImageList1
              OnClick = sbAddMaterialTransformClick
            end
            object sbDeleteMaterialTransform: TSpeedButton
              Left = 0
              Top = 31
              Width = 23
              Height = 22
              ImageIndex = 1
              Images = ImageList1
              OnClick = sbDeleteMaterialTransformClick
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
                Top = 8
                Width = 27
                Height = 13
                Caption = 'Angle'
              end
              object Label17: TLabel
                Left = 155
                Top = 8
                Width = 35
                Height = 13
                Caption = 'radians'
              end
              object ePTAngle: TEdit
                Left = 93
                Top = 5
                Width = 56
                Height = 21
                Alignment = taRightJustify
                TabOrder = 0
                Text = '0'
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
                Alignment = taRightJustify
                TabOrder = 0
                Text = '0'
                OnExit = ePTXExit
              end
              object ePTY: TEdit
                Left = 93
                Top = 34
                Width = 56
                Height = 21
                Alignment = taRightJustify
                TabOrder = 1
                Text = '0'
                OnExit = ePTXExit
              end
              object ePTZ: TEdit
                Left = 93
                Top = 61
                Width = 56
                Height = 21
                Alignment = taRightJustify
                TabOrder = 2
                Text = '0'
                OnExit = ePTXExit
              end
            end
          end
        end
      end
    end
  end
  object pRender: TPanel
    Left = 0
    Top = 41
    Width = 856
    Height = 673
    Align = alClient
    TabOrder = 2
    ExplicitWidth = 852
    ExplicitHeight = 672
    object iRender: TImage
      Left = 7
      Top = 6
      Width = 105
      Height = 105
      AutoSize = True
    end
  end
  object sbMain: TStatusBar
    Left = 0
    Top = 714
    Width = 1145
    Height = 19
    Panels = <>
    SimplePanel = True
    ExplicitTop = 713
    ExplicitWidth = 1141
  end
  object ImageList1: TImageList
    DrawingStyle = dsTransparent
    Left = 704
    Top = 64
    Bitmap = {
      494C01010B001800040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000005050500111111000505050000000000000000000000
      0000000000000000000000000000000000000000000000000000C9C9C9009C9C
      9C0000000000BEBEBE004141410021212100232323003C3C3C00BCBCBC000000
      0000A0A0A000ADADAD0000000000000000000000000000000000000000000000
      0000000000001E1E1E00222222001D1D1D001D1D1D001D1D1D001D1D1D001D1D
      1D001D1D1D001D1D1D001B1B1B00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2E2E200FFFFFF00E1E1E10000000000000000000000
      000000000000000000000000000000000000000000000000000003030300C4C4
      C400AEAEAE00131313000E0E0E000E0E0E000E0E0E000E0E0E0018181800ADAD
      AD00C3C3C3001212120000000000000000000000000000000000000000000000
      00000000000018181800FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF000F0F0F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000021212100DEDEDE00F5F5F500DEDEDE0021212100000000000000
      00000000000000000000000000000000000000000000DBDBDB0041414100A6A6
      A600060606000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000101
      0100BABABA004F4F4F00DBDBDB00000000000000000000000000000000000000
      00000000000029292900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF001F1F1F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000131313001C1C1C00252525001D1D1D0013131300000000000000
      0000000000000000000000000000000000000000000000000000525252000000
      00000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E0000000000585858000000000000000000000000001B1B1B00272727002929
      29002424240013131300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF001D1D1D00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D9D9D90014141400E0E0E000E6E6E600DFDFDF0014141400D9D9D9000000
      0000000000000000000000000000000000000000000000000000BCBCBC000F0F
      0F000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E000D0D0D00BABABA0000000000000000000000000004040400FFFFFF00FFFF
      FF00FFFFFF0023232300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF001D1D1D00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00005858580048484800FFFFFF00FFFFFF00FFFFFF0048484800585858000000
      000000000000000000000000000000000000000000003D3D3D00000000003636
      36000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E0035353500000000003D3D3D00000000000000000021212100FFFFFF00FFFF
      FF00FFFFFF0027272700FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF001D1D1D00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B7B7
      B70000000000E2E2E200FFFFFF00FFFFFF00FFFFFF00E2E2E20000000000B6B6
      B600000000000000000000000000000000000000000017171700000000002F2F
      2F000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E0030303000000000000909090000000000000000001D1D1D00FFFFFF00FFFF
      FF00FFFFFF0026262600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF001D1D1D00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E1E1E1000000
      0000B7B7B700FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B8B8B8000000
      0000E1E1E10000000000000000000000000000000000464646003D3D3D003131
      31000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E0036363600434343002F2F2F0000000000000000001D1D1D00FFFFFF00FFFF
      FF00FFFFFF0026262600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF001F1F1F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000454545005A5A
      5A00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF005B5B
      5B004545450000000000000000000000000000000000E9E9E9003E3E3E000505
      05000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E000000000038383800E7E7E70000000000000000001D1D1D00FFFFFF00FFFF
      FF00FFFFFF0026262600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0011111100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000015151500D8D8
      D800FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00D9D9
      D90015151500000000000000000000000000000000000000000000000000D1D1
      D100000000000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E001414
      1400C2C2C200000000000000000000000000000000001D1D1D00FFFFFF00FFFF
      FF00FFFFFF0026262600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF002424
      24004C4C4C001919190003030300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000028222800F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F4F4
      F400232323000000000000000000000000000000000000000000F0F0F0004646
      4600030303002C2C2C000E0E0E000E0E0E000E0E0E000E0E0E00252525000A0A
      0A0053535300F0F0F0000000000000000000000000001D1D1D00FFFFFF00FFFF
      FF00FFFFFF0027272700FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF003838
      38008B8B8B000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000016161600DADA
      DA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00DADA
      DA00161616000000000000000000000000000000000000000000242424007272
      7200000000009F9F9F00000000002B2B2B002B2B2B00000000007D7D7D000000
      00007A7A7A002D2D2D000000000000000000000000001D1D1D00FFFFFF00FFFF
      FF00FFFFFF0006060600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000202
      0200000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003D3D3D006262
      6200FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006262
      62003D3D3D0000000000000000000000000000000000000000000E0E0E000000
      000000000000ABABAB007B7B7B000E0E0E000E0E0E0086868600A0A0A0000000
      000000000000020202000000000000000000000000001D1D1D00FFFFFF00FFFF
      FF00FFFFFF00262626002424240027272700505050000C0C0C00000000000A0A
      0A00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000DADADA000000
      0000B3B3B300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B4B4B4000000
      0000DADADA0000000000000000000000000000000000000000002C2C2C00F2F2
      F20000000000A9A9A900080808000E0E0E000E0E0E000A0A0A00979797000000
      0000E7E7E700292929000000000000000000000000001F1F1F00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00F7F7F700FEFEFE00A0A0A00000000000B6B6B6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B2B2
      B200000000006D6D6D00D5D5D500F5F5F500D5D5D5006C6C6C0000000000B2B2
      B200000000000000000000000000000000000000000000000000F6F6F6000000
      0000E5E5E500313131007C7C7C00202020001F1F1F008585850031313100E2E2
      E20000000000F3F3F3000000000000000000000000000F0F0F00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000C4C4C400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DBDBDB004F4F4F001F1F1F00111111001F1F1F0050505000DBDBDB000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E0E0E00000000000F6F6F600F6F6F60000000000E1E1E1000000
      000000000000000000000000000000000000000000001B1B1B001D1D1D001D1D
      1D001D1D1D001D1D1D001D1D1D0011111100CFCFCF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001111
      1100111111001111110012121200121212001111110011111100111111000808
      0800111111001313130000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000F0F0F00EAEA
      EA00F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500F8F8F800FDFD
      FD00F6F6F6001111110000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000013131300FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FDFDFD001111110000000000000000001111110036363600272727002626
      2600252525002626260026262600262626002525250025252500262626002525
      2500383838000000000000000000000000001313130026262600252525002626
      2600262626002525250026262600262626002525250027272700515151000505
      0500000000002727270048484800151515000000000000000000000000000000
      0000AEAEAE00AEAEAE0000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000012121200F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00131313000000000000000000000000006E6E6E00F2F2F200E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E6E6E600E6E6E600E5E5E500E4E4
      E4000000000092929200000000000000000000000000DBDBDB00E5E5E500E5E5
      E500E6E6E600E5E5E500E5E5E500E5E5E500E6E6E600FFFFFF00989898000000
      0000ABABAB00FDFDFD00A8A8A80000000000000000000000000000000000BBBB
      BB000000000000000000BBBBBB00000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000011111100F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F9F9F9001111110000000000000000000202020000000000FEFEFE00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00B7B7B70000000000000000000000000013131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CBCBCB0004040400BCBC
      BC00FFFFFF00CDCDCD0000000000131313000000000000000000B6B6B6000000
      0000CCCCCC00CCCCCC0000000000B6B6B6000000000000000000000000000000
      000000000000000000000000000000000000000000000000000012121200F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F5001212120000000000000000004C4C4C003232320066666600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000C0C0C008F8F8F000000000013131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C4C4C400000000007E7E7E00FFFF
      FF00B3B3B30000000000A9A9A9003D3D3D0000000000B5B5B50000000000B4B4
      B4000000000000000000B4B4B40000000000B6B6B60000000000000000000000
      000000000000000000000000000000000000000000000000000011111100F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F5001212120000000000000000003D3D3D00DADADA0000000000E5E5
      E500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00B7B7B700000000000000000000000000C3C3C300FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00B5B5B5000000000089898900404040007A7A
      7A0000000000C1C1C100FFFFFF00101010009A9A9A0000000000B5B5B5000000
      0000000000000000000000000000B6B6B60000000000B5B5B500000000000000
      000000000000000000000000000000000000000000000000000011111100F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F5001212120000000000000000000E0E0E00FFFFFF00666666004949
      4900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0028282800909090001111110000000000BEBEBE00FFFF
      FF00FFFFFF00FFFFFF00B6B6B60000000000B2B2B200FFFFFF00BABABA000000
      0000BEBEBE00FFFFFF00F6F6F6001010100072727200A6A6A600000000000000
      000000000000000000000000000000000000B6B6B60000000000B5B5B5000000
      000000000000000000000000000000000000000000000000000011111100F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F5001212120000000000000000000E0E0E00FFFFFF00F0F0F0000000
      0000C4C4C400E5E5E500E5E5E500E5E5E500E6E6E600E5E5E500E5E5E500E8E8
      E800F3F3F300EBEBEB00A2A2A200000000003E3E3E00AAAAAA0000000000B2B2
      B200FFFFFF00B2B2B20000000000B5B5B500FFFFFF00FFFFFF00FFFFFF00FAFA
      FA00FFFFFF00FFFFFF00F3F3F300111111000000000000000000000000000000
      00000000000000000000000000000000000000000000B5B5B50000000000B5B5
      B50000000000000000000000000000000000000000000000000011111100F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F50011111100000000000000000012121200F7F7F700FFFFFF009494
      9400060606002626260026262600252525002525250026262600262626002424
      2400141414002424240042424200484848000F0F0F00FFFFFF00C1C1C1000000
      00007979790000000000B5B5B500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00EFEFEF00FEFEFE00F6F6F600121212000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B5B5B5000000
      0000B5B5B500000000000000000000000000000000000000000011111100F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F50012121200000000000000000011111100F5F5F500FFFFFF00FFFF
      FF00EBEBEB00EFEFEF00F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500DADA
      DA0004040400CBCBCB0000000000000000000F0F0F00F6F6F600FFFFFF00BDBD
      BD0000000000BEBEBE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EDED
      ED006D6D6D00FAFAFA00FDFDFD00111111000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B6B6
      B60000000000B5B5B5000000000000000000000000000000000011111100F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F50011111100000000000000000013131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500DADA
      DA000000000000000000000000000000000013131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FCFCFC00FFFFFF00FFFFFF00131313000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B6B6B60000000000B6B6B60000000000000000000000000006060600F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F50012121200000000000000000000000000DCDCDC00E5E5E500E5E5
      E500AAAAAA002525250026262600252525002525250025252500262626002424
      24005A5A5A0000000000000000000000000000000000DCDCDC00E5E5E500E7E7
      E700F2F2F200E7E7E700E6E6E600E6E6E600E5E5E500E5E5E500E5E5E500E7E7
      E700EFEFEF00E6E6E600DBDBDB00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000B6B6B600000000009A9A9A00000000000000000000000000B5B5
      B500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF001313130000000000000000005353530026262600252525002626
      260024242400AAAAAA0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001313130026262600252525002626
      2600252525002626260025252500262626002525250026262600252525002626
      2600252525002525250026262600121212000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700737373000000000000000000000000000000
      0000B5B5B500F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500F5F5
      F500EBEBEB000F0F0F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000001111110012121200111111001212120012121200111111001111
      1100111111000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B4B4B4000E0E0E000F0F
      0F000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E000E0E0E000E0E0E000E0E0E001B1B1B000000000090909000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00090909000000000000000000090909000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00090909000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009B9B9B0000000000D1D1D1005F5F
      5F006E6E6E00B2B2B2000C0C0C00DDDDDD00DDDDDD00DDDDDD00272727006E6E
      6E00DDDDDD00DDDDDD00C0C0C0000000000000000000DBDBDB00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00DBDBDB000000000000000000DBDBDB00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00DBDBDB00000000000000000000000000000000000000
      0000000000009A9A9A000C0C0C0000000000000000000D0D0D009A9A9A000000
      00000000000000000000000000000000000000000000C4C4C400FFFFFF005D5D
      5D0091919100D7D7D70000000000FFFFFF00FFFFFF00FFFFFF00333333008A8A
      8A00FFFFFF00FFFFFF00F1F1F1000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00BFBFBF00BFBFBF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C000000000000000000000000000000000000000
      00000000000000000000A3A3A30029292900282828009C9C9C00000000000000
      0000000000000000000000000000000000000A0A0A00EEEEEE00FFFFFF004848
      480073737300FFFFFF00D1D1D100FFFFFF00FFFFFF00FFFFFF00363636007777
      7700FFFFFF00FFFFFF00DDDDDD000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF001C1C1C001C1C1C00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C000000000000606060006060600070707000606
      0600070707000707070008080800020202000202020007070700050505000505
      05000404040004040400050505000E0E0E000E0E0E00DDDDDD00FFFFFF005050
      5000000000008A8A8A00A8A8A8007F7F7F007F7F7F007F7F7F00000000007F7F
      7F00FFFFFF00FFFFFF00DDDDDD000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF003434340034343400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000FEFEFE00FEFEFE00FCFC
      FC00FCFCFC00FEFEFE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FBFBFB00FCFCFC00F9F9F900010101000E0E0E00DDDDDD00FFFFFF00B3B3
      B300565656002E2E2E002E2E2E002E2E2E002E2E2E002E2E2E005D5D5D00C7C7
      C700FFFFFF00FFFFFF00DDDDDD000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF003E3E3E003E3E3E00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000E0E0E00DCDCDC00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00DCDCDC000E0E0E0000000000C0C0C000FFFFFF00BFBF
      BF003636360036363600363636000B0B0B000B0B0B0036363600363636003636
      3600BFBFBF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00BFBF
      BF003636360036363600363636000B0B0B000B0B0B0036363600363636003636
      3600BFBFBF00FFFFFF00C0C0C0000000000002020200FEFEFE00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FDFDFD00020202000E0E0E00DFDFDF00FAFAFA00F3F3
      F300F0F0F000F0F0F000F0F0F000F0F0F000F0F0F000F0F0F000F0F0F000EEEE
      EE00F1F1F100FAFAFA00DFDFDF000E0E0E0000000000C0C0C000FFFFFF00BFBF
      BF003636360036363600363636000B0B0B000B0B0B0036363600363636003636
      3600BFBFBF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00BFBF
      BF003636360036363600363636000B0B0B000B0B0B0036363600363636003636
      3600BFBFBF00FFFFFF00C0C0C0000000000002020200FCFCFC00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00020202000E0E0E00F4F4F4008A8A8A000A0A
      0A00020202000202020002020200020202000202020002020200020202000202
      02000A0A0A008A8A8A00F4F4F4000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF003E3E3E003E3E3E00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000002020200FBFBFB00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00040404000E0E0E00F7F7F7004F4F4F005858
      5800CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00585858004F4F4F00F7F7F7000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF003434340034343400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000005050500FDFDFD00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00030303000E0E0E00F6F6F6004E4E4E008A8A
      8A00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF008A8A8A004E4E4E00F6F6F6000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF001C1C1C001C1C1C00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000002020200FCFCFC00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00020202000E0E0E00F6F6F600545454007F7F
      7F00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF007F7F7F0054545400F6F6F6000E0E0E0000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00BFBFBF00BFBFBF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000000000000C0C0C000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00C0C0C0000000000003030300FEFEFE00FFFFFF00FDFD
      FD00FDFDFD00FDFDFD00FDFDFD00FDFDFD00FDFDFD00FDFDFD00FDFDFD00FDFD
      FD00FEFEFE00FEFEFE00FDFDFD00000000000E0E0E00F6F6F600545454007F7F
      7F00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF007F7F7F0054545400F6F6F6000E0E0E0000000000DBDBDB00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00DBDBDB000000000000000000DBDBDB00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00DBDBDB00000000000404040001010100020202000202
      0200020202000202020002020200020202000202020002020200020202000202
      0200020202000202020001010100090909000D0D0D00FFFFFF005C5C5C008A8A
      8A00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF008A8A8A005C5C5C00FFFFFF000D0D0D000000000090909000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00090909000000000000000000090909000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00090909000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D5D5D500474747006E6E
      6E00DDDDDD00DDDDDD00DDDDDD00DDDDDD00DDDDDD00DDDDDD00DDDDDD00DDDD
      DD006E6E6E0047474700D5D5D500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000005A5A5A000E0E0E000E0E0E000E0E
      0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E0E000E0E
      0E000E0E0E000E0E0E000E0E0E005A5A5A00424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF00FC7FC813F8010000F83FC003F8010000
      F83F8001F8010000F83FC00380010000F01FC00380010000F01FA00580010000
      E00FA00580010000C007800180010000C007800180010000C007E00780010000
      C007C00380030000C007C81380070000C007D81B800F0000C007C813801F0000
      E00FD00B803F0000F01FFA5F807F0000C003FFFFFFFFFFFFC003FFFFFFFFFFFF
      C00300070000F3FFC00300030000E1FFC00300030000C0FFC003000100008C7F
      C003000100001E3FC003000000003F1FC00300000000FF8FC00300000000FFC7
      C00300030000FFE3C00300070000FFF1C00300070000FFF8C00303FF0000FFFC
      E003FFFFFFFFFFFFF003FFFFFFFFFFFF00000000FFFF800000000000FFFF0000
      00000000F81F000000000000FC3F000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FFFF000000000000FFFF000000000000000000000000000000000000
      000000000000}
  end
  object MainMenu1: TMainMenu
    Left = 624
    Top = 64
    object File1: TMenuItem
      Caption = 'File'
      object Openproject1: TMenuItem
        Caption = 'Open project...'
        OnClick = bOpenSceneClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Saveproject1: TMenuItem
        Caption = 'Save project...'
        OnClick = bSaveSceneClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Exportrender1: TMenuItem
        Caption = 'Export render...'
        OnClick = bSaveImageClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object File2: TMenuItem
        Caption = 'Exit'
        OnClick = File2Click
      end
    end
    object Render1: TMenuItem
      Caption = 'Render'
      object Render2: TMenuItem
        Caption = 'Render'
        ShortCut = 120
        OnClick = bRenderClick
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Caption = 'About...'
        OnClick = bAboutClick
      end
    end
  end
end
