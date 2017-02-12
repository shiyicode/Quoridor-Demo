<GameFile>
  <PropertyGroup Name="lResultLayer" Type="Scene" ID="b68c6b47-6685-486a-9f21-f2daec09c19d" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="87" ctype="GameNodeObjectData">
        <Size X="640.0000" Y="1024.0000" />
        <Children>
          <AbstractNodeData Name="bgSprite" ActionTag="361730848" Tag="88" IconVisible="False" LeftMargin="9.4987" RightMargin="-0.4988" TopMargin="198.1663" BottomMargin="194.8337" ctype="SpriteObjectData">
            <Size X="631.0000" Y="631.0000" />
            <Children>
              <AbstractNodeData Name="gameresult_win_2" ActionTag="-1002885728" Tag="89" IconVisible="False" LeftMargin="132.0000" RightMargin="123.0000" TopMargin="-55.3174" BottomMargin="464.3174" ctype="SpriteObjectData">
                <Size X="376.0000" Y="222.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="575.3174" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5071" Y="0.9118" />
                <PreSize X="0.5959" Y="0.3518" />
                <FileData Type="PlistSubImage" Path="gameresult_lose.png" Plist="Plist/GameResultLayer.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="gameresult_splitter_3" ActionTag="-12552225" Tag="90" IconVisible="False" LeftMargin="285.2835" RightMargin="171.7165" TopMargin="234.8441" BottomMargin="390.1559" ctype="SpriteObjectData">
                <Size X="174.0000" Y="6.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="372.2835" Y="393.1559" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5900" Y="0.6231" />
                <PreSize X="0.2758" Y="0.0095" />
                <FileData Type="PlistSubImage" Path="gameresult_splitter.png" Plist="Plist/GameResultLayer.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="head" ActionTag="-2017467944" Tag="91" IconVisible="False" LeftMargin="173.9544" RightMargin="346.0456" TopMargin="181.4896" BottomMargin="341.5104" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="81" Scale9Height="86" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="111.0000" Y="108.0000" />
                <AnchorPoint ScaleX="0.5494" ScaleY="0.4789" />
                <Position X="234.9378" Y="393.2316" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3723" Y="0.6232" />
                <PreSize X="0.1759" Y="0.1712" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Normal" Path="Image/headFrame.png" Plist="" />
                <PressedFileData Type="Normal" Path="Image/headFrame.png" Plist="" />
                <NormalFileData Type="Normal" Path="Image/headFrame.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="gameresult_halo_win_12" ActionTag="1047847872" Tag="92" IconVisible="False" LeftMargin="160.6662" RightMargin="148.3338" TopMargin="241.0000" BottomMargin="92.0000" ctype="SpriteObjectData">
                <Size X="322.0000" Y="298.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="321.6662" Y="241.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5098" Y="0.3819" />
                <PreSize X="0.5103" Y="0.4723" />
                <FileData Type="PlistSubImage" Path="gameresult_halo_lose.png" Plist="Plist/GameResultLayer.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="score" ActionTag="-2076441800" Tag="93" IconVisible="False" LeftMargin="181.0000" RightMargin="172.0000" TopMargin="334.5000" BottomMargin="185.5000" ctype="SpriteObjectData">
                <Size X="278.0000" Y="111.0000" />
                <Children>
                  <AbstractNodeData Name="num" ActionTag="-1843035221" Tag="94" IconVisible="False" LeftMargin="92.2078" RightMargin="125.7922" TopMargin="19.2111" BottomMargin="20.7889" FontSize="48" LabelText="-10" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ShadowEnabled="True" ctype="TextObjectData">
                    <Size X="60.0000" Y="71.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="122.2078" Y="56.2889" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="0" B="0" />
                    <PrePosition X="0.4396" Y="0.5071" />
                    <PreSize X="0.2158" Y="0.6396" />
                    <FontResource Type="Normal" Path="level.ttf" Plist="" />
                    <OutlineColor A="255" R="0" G="0" B="0" />
                    <ShadowColor A="255" R="0" G="0" B="0" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="gameresult_label_score_15" ActionTag="249135201" Tag="95" IconVisible="False" LeftMargin="169.1163" RightMargin="53.8837" TopMargin="16.1794" BottomMargin="21.8206" ctype="SpriteObjectData">
                    <Size X="55.0000" Y="73.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="196.6163" Y="58.3206" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7073" Y="0.5254" />
                    <PreSize X="0.1978" Y="0.6577" />
                    <FileData Type="PlistSubImage" Path="gameresult_label_score.png" Plist="Plist/GameResultLayer.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="241.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5071" Y="0.3819" />
                <PreSize X="0.4406" Y="0.1759" />
                <FileData Type="PlistSubImage" Path="gameresult_bg_score.png" Plist="Plist/GameResultLayer.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="level" ActionTag="783200095" Tag="96" IconVisible="False" LeftMargin="349.3197" RightMargin="233.6803" TopMargin="249.9601" BottomMargin="353.0399" FontSize="24" LabelText="一级" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="48.0000" Y="28.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="373.3197" Y="367.0399" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.5916" Y="0.5817" />
                <PreSize X="0.0761" Y="0.0444" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="name" ActionTag="-578395848" Tag="97" IconVisible="False" LeftMargin="304.5672" RightMargin="182.4328" TopMargin="197.1085" BottomMargin="405.8915" IsCustomSize="True" FontSize="24" LabelText="你若乘风归去" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="144.0000" Y="28.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="376.5672" Y="419.8915" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.5968" Y="0.6654" />
                <PreSize X="0.2282" Y="0.0444" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="continue" ActionTag="442194872" Tag="98" IconVisible="False" LeftMargin="239.0000" RightMargin="230.0000" TopMargin="462.7029" BottomMargin="108.2971" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="132" Scale9Height="38" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="162.0000" Y="60.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="320.0000" Y="138.2971" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5071" Y="0.2192" />
                <PreSize X="0.2567" Y="0.0951" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="PlistSubImage" Path="gameresult_button_again_down.png" Plist="Plist/GameResultLayer.plist" />
                <PressedFileData Type="PlistSubImage" Path="gameresult_button_again_down.png" Plist="Plist/GameResultLayer.plist" />
                <NormalFileData Type="PlistSubImage" Path="gameresult_button_again_up.png" Plist="Plist/GameResultLayer.plist" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="324.9987" Y="510.3337" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5078" Y="0.4984" />
            <PreSize X="0.9859" Y="0.6162" />
            <FileData Type="Normal" Path="Image/bg_gameresult.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>