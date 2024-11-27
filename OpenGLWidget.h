#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
public:
    OpenGLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

protected:
    void singleVboBind();
    void multVboBind();

    void singleVboAndVaoBind();
    void interLeavedBuffer();


};

#endif // OPENGLWIDGET_H
