import QtQuick 2.7
import QtQuick.Window 2.2
import Sensor 1.0

Window {
    id: mainWindow
    visible: true
    width: 600
    height: 800
    title: qsTr("My Gas Detector")
    Rectangle{
        id: mainRect
        anchors.fill: parent
        property string m_color: cl.currentColor
        property bool changeColorTrigger: false
        onM_colorChanged: {
            changeColorTrigger = false
            changeColorTrigger = true
        }

        Text {
          id: mainText

          text: cl.description

          font.pixelSize: SH.dp(70)
          anchors.centerIn: parent


//          Behavior on text {
//            SequentialAnimation {
//              NumberAnimation { target: mainText; property: "opacity"; to: 0 }
//              PropertyAction { }
//              NumberAnimation { target: mainText; property: "opacity"; to: 1 }
//            }
//          }
        }


//        Behavior on color {

//            ColorAnimation {

//                duration: 1500
//            }
//        }

        gradient: Gradient {
          GradientStop {
            position: 1
            color: mainRect.changeColorTrigger == true ? cl.currentColor  : cl.currentColor

            Behavior on color { ColorAnimation { duration: 2500 } }
          }
          GradientStop {
            position: 0
            color: mainRect.changeColorTrigger == true ? cl.currentColor  : cl.currentColor

            Behavior on color { ColorAnimation { duration: 1500 } }
          }
        }

    }

    Menu {
        id: cl
        width: parent.width
        height: parent.height
        collapsedHeight: mainWindow.height * 0.1
        property int currentIndex: -1
        property string currentColor: "#000000"
        property string description: ""
        Repeater {

//                model: SensorModel {
//                    list: sensorList
//                }
            model: sensorModel
                MenuItem {
                    color: model.color
                    description: model.description
                    collapsed: cl.collapsed
                    m_index: index
                    title: model.title+" ("+model.sensorName.split("_")[0]+")"
                    //icon: "qrc:/images/services@2x.png"

                }
            }
//        MenuItem {
//            color: "#D77EFC"
//            collapsed: cl.collapsed
//            m_index: 0
//            title: "Air Quality (OFFLINE)"
//            //icon: "qrc:/images/services@2x.png"

//        }

//        MenuItem {
//            color: "#FC6F61"
//            collapsed: cl.collapsed
//            m_index: 1
//            title: "CARBON MONOXIDE (ONLINE)"
//            //icon: "qrc:/images/work@2x.png"
//        }

//        MenuItem {
//            visible: true
//            color: "#18A0FA"
//            collapsed: cl.collapsed
//            m_index: 2
//            title: "Temperateur (ONLINE)"
//            //icon: "qrc:/images/auto@2x.png"
//        }

//        MenuItem {
//            color: "#94C325"
//            collapsed: cl.collapsed
//            m_index: 3
//            title: "humidity (ONLINE)"
//            //icon: "qrc:/images/realty@2x.png"
//        }
    }
}
