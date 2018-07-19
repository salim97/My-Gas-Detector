import QtQuick 2.7
import QtGraphicalEffects 1.0

Item {

    // ----- Public Properties ----- //

    property bool selected: false
    property bool collapsed: false
    property alias icon: imgIcon.source

    property alias title: lbTitle.text
    property alias color: rectShadow.color
    property int m_index: 0
    property int childrenLength: parent.children.length - 1
    property string description: ""
    property alias font: lbTitle.font

    id: root
    width: parent.width
    height: _getHeight()
    z: childrenLength - m_index

    Behavior on height { NumberAnimation { duration: 750; easing.type: Easing.OutExpo } }
    onSelectedChanged:  {
        if(selected){
            parent.currentIndex = index
            parent.currentColor = color
//            parent.description = description
            parent.description = Qt.binding(function() { return description })
        }
    }
    DropShadow {
        anchors.fill: rectShadow
        horizontalOffset: 0
        verticalOffset: 5
        radius: root.selected ? 8.0 : 16.0
        samples: 1 + radius * 2
        color: "#80000000"
        source: rectShadow
    }

    Rectangle {
        id: rectShadow
        anchors.fill: parent
    }

    Item {
        id: container
        width: parent.width
        height: root.collapsed ? lbTitle.contentHeight : ((imgIcon.visible ? imgIcon.height : 0) + lbTitle.contentHeight)
        anchors.centerIn: parent

        Image {
            id: imgIcon
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            visible: !root.collapsed || !(status === Image.Null)
            scale: root.collapsed ? 0 : 1

            Behavior on scale { NumberAnimation { duration: 200 } }
        }

        Text {
            id: lbTitle
            anchors {
                top: root.collapsed ? parent.top : imgIcon.bottom
                horizontalCenter: parent.horizontalCenter
            }
            font.pixelSize: SH.dp(20)
            visible: !(scale === 0)
            color: "white"
            scale: root.collapsed && !root.selected ? 0 : 1

            Behavior on scale { NumberAnimation { duration: 200 } }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.selected = !root.selected;
            root.parent.toggle();
        }
    }

    // ----- Private Functions ----- //

    function _getHeight() {
        if (!selected && collapsed) {
            return 0;
        }
        else if (selected && collapsed) {
            return root.parent.collapsedHeight;
        }

        return parent.height / childrenLength ;
    }
}
