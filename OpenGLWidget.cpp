#include "OpenGLWidget.h"
#include <QDebug>

float vertex[] = {
    0.0, 0.5, 0.0,
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0
};

float colors[] = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0
};

float posColor[] = {
    0.0, 0.05, 0.0, 1.0, 0.0, 0.0,
    -0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
    0.5, -0.5, 0.0, 0.0, 0.0, 1.0
};

const char* vertexSource ={
    "#version 330 core \n"
    "layout (location = 0) in vec3 aPos; \n"
    "void main() \n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"
};

const char* fragmentSource = {
    "#version 330 core\n"
    "out vec4 fragColor; \n"
    "void main()\n"
    "{\n"
    "   fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\0"
};

GLuint VAO = 0;
GLuint program = 0;

OpenGLWidget::OpenGLWidget()
{

}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glViewport(0, 0, 800, 600);

    // //创建一个VBO VBO就是一块显存的编号
    // GLuint vbo = 0;
    // glGenBuffers(1, &vbo);
    // //绑定当前vbo到状态机
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // //数据传输给当前vbo，同时开辟显存
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

   // singleVboBind();

  //  multVboBind();

   // singleVboAndVaoBind();

  //  interLeavedBuffer();

    GLuint posVBO = 0;
    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER,posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    GLuint colorVBO;
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    GLuint posShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(posShader, 1, &vertexSource, nullptr);
    glCompileShader(posShader);
    int success = -1;
    glGetShaderiv(posShader, GL_COMPILE_STATUS, &success);
    if(GL_FALSE == success)
    {
        char logInfo[1024];
        glGetShaderInfoLog(posShader, 1024, nullptr, logInfo);
        qDebug()<<"编译vertex shader 错误信息："<<logInfo;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(GL_FALSE == success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
        qDebug()<<"fragment shader error"<<infoLog;
    }

    program = glCreateProgram();
    glAttachShader(program, posShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(posShader);
    glDeleteShader(fragmentShader);
}

void OpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.8, 0.8, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

//顶点和颜色数据存在两个不同的数组，顶点VBO和颜色VBO分别申请显存
void OpenGLWidget::singleVboBind()
{
    GLuint posVbo = 0;
    //创建位置VBO
    glGenBuffers(1, &posVbo);
    //绑定当前VBO
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    //数据传送到当前VBO，并开辟显存
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    GLuint colorVbo = 0;
    //创建颜色VBO
    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

//顶点和颜色数据存在一个数组，一次性给顶点和颜色分配VBO
void OpenGLWidget::multVboBind()
{
    GLuint posColorVbo = 0;
    glGenBuffers(1, &posColorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posColorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posColor), posColor, GL_STATIC_DRAW);
}

//顶点和颜色在不同的数组中
void OpenGLWidget::singleVboAndVaoBind()
{
    //创建顶点VBO
    GLuint posVbo = 0;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    //给posVBO分配数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    //创建颜色VBO
    GLuint colorVbo = 0;
    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    //给颜色VBO分配数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    //创建VAO
    GLuint posVao = 0;
    glGenVertexArrays(1, &posVao);
    glBindVertexArray(posVao);
    //绑定当前位置VBO,使得下面的功能与该VBO关联，将posVbo的信息存在该VAO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    //创建颜色VAO
    GLuint colorVao = 0;
    glGenVertexArrays(1, &colorVao);
    glBindVertexArray(colorVao);
    //绑定当前VBO
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);


}

//位置和颜色在同一个数组中
void OpenGLWidget::interLeavedBuffer()
{
    //创建VBO
    GLuint posColorVBO = 0;
    glGenBuffers(1, &posColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posColor), posColor, GL_STATIC_DRAW);

    //创建顶点VBO
    GLuint posColorVAO = 0;
    glGenVertexArrays(1, &posColorVAO);
    glBindVertexArray(posColorVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

    //解除VAO的绑定
    glBindVertexArray(0);
}
