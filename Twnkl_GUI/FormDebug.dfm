object frmDebug: TfrmDebug
  Left = 0
  Top = 0
  Caption = 'frmDebug'
  ClientHeight = 442
  ClientWidth = 634
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnShow = FormShow
  TextHeight = 15
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 634
    Height = 401
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 624
    ExplicitHeight = 400
    object TabSheet1: TTabSheet
      Caption = 'Loader'
      object mLoader: TMemo
        Left = 0
        Top = 0
        Width = 626
        Height = 371
        Align = alClient
        Lines.Strings = (
          'mLoader')
        TabOrder = 0
        ExplicitWidth = 620
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'World'
      ImageIndex = 1
      object mWorld: TMemo
        Left = 0
        Top = 0
        Width = 626
        Height = 371
        Align = alClient
        Lines.Strings = (
          'mLoader')
        TabOrder = 0
        ExplicitWidth = 616
        ExplicitHeight = 370
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 401
    Width = 634
    Height = 41
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 403
    ExplicitWidth = 628
    DesignSize = (
      634
      41)
    object OK: TBitBtn
      Left = 550
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = 'OK'
      ModalResult = 2
      TabOrder = 0
      ExplicitLeft = 544
    end
  end
end
