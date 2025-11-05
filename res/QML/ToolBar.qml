import QtQuick 2.15
import QtQuick.Controls

ListView {
    id: listView
    width: 56
    height: shapesModel.count * 56
    model: shapesModel
    spacing: 0
    clip: true
    interactive: false

    ListModel {
        id: shapesModel
        ListElement {check: true  ; icon: "qrc:/ICON/ToolBar/Move.svg"     ; activeIcon: "qrc:/ICON/ToolBar/Move_Active.svg"     ; shapeName: "Move"}
        ListElement {check: false ; icon: "qrc:/ICON/ToolBar/Line.svg"     ; activeIcon: "qrc:/ICON/ToolBar/Line_Active.svg"     ; shapeName: "Line"}
        ListElement {check: false ; icon: "qrc:/ICON/ToolBar/Ellipse.svg"  ; activeIcon: "qrc:/ICON/ToolBar/Ellipse_Active.svg"  ; shapeName: "Ellipse"}
        ListElement {check: false ; icon: "qrc:/ICON/ToolBar/Rectangle.svg"; activeIcon: "qrc:/ICON/ToolBar/Rectangle_Active.svg"; shapeName: "Rectangle"}
        ListElement {check: false ; icon: "qrc:/ICON/ToolBar/Path.svg"     ; activeIcon: "qrc:/ICON/ToolBar/Path_Active.svg"     ; shapeName: "Path"}
        ListElement {check: false ; icon: "qrc:/ICON/ToolBar/Polygon.svg"  ; activeIcon: "qrc:/ICON/ToolBar/Polygon_Active.svg"  ; shapeName: "Polyon"}
    }

    delegate : AbstractButton {
        id: aBtn
        width: 56
        height: width
        checkable: true
        autoExclusive: true
        checked: check

        onCheckedChanged: {
            if(checked)
                myView.setTool(index)
        }

        background: Rectangle {
            id: delegateRoot
            color: aBtn.checked ? "#000" : aBtn.hovered ? "#3d3d3d" : "#222"

            Image {
                id: svgIcon
                sourceSize.width: parent.width * 0.8
                source: aBtn.checked ? model.activeIcon : model.icon
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                smooth: true
            }
        }
    }
}
