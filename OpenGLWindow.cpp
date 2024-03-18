#include "stdafx.h"
#include "OpenGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>
#include "Triangulation.h"
#include "Point3D.h"
#include "Reader.h"
#include "Waterpath.h"
#include "Findpath.h"

Triangulation triangulation;
Reader reader;
vector<Point3D>& points = triangulation.uniquePoints();
vector<Triangle>& triangles = triangulation.triangles();
int verticesPerTriangle;
int coordinatesPerVertex;
int totalVertices;
int totalCoordinates;
GLfloat* vertices;
GLfloat* colors;
//GLfloat* waterFlow;
//GLfloat* colorsPath;

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}
OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    // And now release all OpenGL resources.
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    QMatrix4x4 scaleMatrix;
    QMatrix4x4 rotationMatrix;
    //matrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    matrix.perspective(60.0f * scaleFactor, 4.0f / 3.0f * scaleFactor, 0.1f, 1000.0f);
    matrix.translate(0, 0, -10);
    matrix.rotate(rotationAngle);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    

    

    //Triangulation triangulation;
    //Reader reader;
    //reader.readFile(triangulation);

    //vector<Point3D>& points = triangulation.uniquePoints();
    //vector<Triangle>& triangles = triangulation.triangles();

    //static const int verticesPerTriangle = 3;
    //static const int coordinatesPerVertex = 3;
    //static const int totalVertices = verticesPerTriangle * triangles.size();
    //static const int totalCoordinates = totalVertices * coordinatesPerVertex;

    //GLfloat* vertices = new GLfloat[totalCoordinates];
    //int currentIndex = 0;

    //for (const Triangle& triangle : triangles)
    //{
    //    // Iterate over each vertex of the triangle
    //    for (int i = 0; i < verticesPerTriangle; ++i)
    //    {
    //        // Get the index of the current vertex of the triangle
    //        int vertexIndex;
    //        if (i == 0)
    //            vertexIndex = triangle.v1();
    //        else if (i == 1)
    //            vertexIndex = triangle.v2();
    //        else
    //            vertexIndex = triangle.v3();

    //        // Append coordinates of the vertex to vertices array
    //        vertices[currentIndex++] = points[vertexIndex].x();
    //        vertices[currentIndex++] = points[vertexIndex].y();
    //        vertices[currentIndex++] = points[vertexIndex].z();
    //    }
    //}
    //size_t sizeOfVertices = totalCoordinates * sizeof(GLfloat);

    //GLfloat* colors = new GLfloat[totalCoordinates];

    //for (int i = 0; i < totalCoordinates; i += 3) {
    //    colors[i] = 1.0f;
    //    colors[i + 1] = 1.0f;
    //    colors[i + 2] = 0.0f;
    //}


    // WaterPath ww;
    //HighestPoint pp;
    //vector<Point3D> waterPath;

    //GLfloat* waterFlow = new GLfloat[waterPath.size()];
    //Point3D firstPoint;
    //firstPoint = pp.findHighestPoint(triangulation);
    //pp.findNextPoint(firstPoint, triangulation, 1.0, waterPath);
    //for (int i = 0; i < waterPath.size(); i+=3) {
    //    waterFlow[i] = waterPath[i].x();
    //    waterFlow[i+1] = waterPath[i].y();
    //    waterFlow[i+2] = waterPath[i].z();
    //    
    //}


    //GLfloat* colorsPath = new GLfloat[waterPath.size()];

    //for (int i = 0; i < waterPath.size(); i += 3) {
    //    colorsPath[i] = 0.0f;
    //    colorsPath[i + 1] = 0.0f;
    //    colorsPath[i + 2] = 1.0f;
    //}

    /*GLfloat waterFlow1[] = {
        73.01, 88.88, 47.31,
        72.61, 89.28, 47.17,
        72.22, 89.68, 46.94,
        71.82, 90.07, 46.67,
        71.42, 90.47, 46.25,
        71.03, 90.87, 45.81
    };

    GLfloat waterFlowColor[] = {
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0
    };*/

    WaterPath ww;
    HighestPoint pp;
    path ff;

    vector<Point3D> waterPath;

    Point3D firstPoint;
    /*firstPoint = pp.findHighestPoint(triangulation);
    pp.findNextPoint(firstPoint, triangulation, 1.0, waterPath);*/
    waterPath = ff.findpath(triangulation);
    vector<GLfloat> waterFlow;
    //waterFlow = new GLfloat[waterPath.size()];
    for (int i = 0; i < waterPath.size(); i++) {
        /*waterFlow[i] = waterPath[i].x();
        waterFlow[i + 1] = waterPath[i].y();
        waterFlow[i + 2] = waterPath[i].z();*/
        waterFlow.push_back(waterPath[i].x());
        waterFlow.push_back(waterPath[i].y());
        waterFlow.push_back(waterPath[i].z());

    }

    vector<GLfloat> colorsPath;
    //colorsPath = new GLfloat[waterPath.size()];

    for (int i = 0; i < waterPath.size(); i++) {
        /*colorsPath[i] = 0.0f;
        colorsPath[i + 1] = 0.0f;
        colorsPath[i + 2] = 1.0f;*/
        colorsPath.push_back(0.0f);
        colorsPath.push_back(0.0f);
        colorsPath.push_back(1.0f);

    }

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, totalCoordinates / 3);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, waterFlow.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsPath.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    //int size = waterPath.size();
    glLineWidth(20.0f);
    glDrawArrays(GL_LINE_LOOP, 0, waterFlow.size()/3);
    glLineWidth(1.0f);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}


void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";
    rotationAngle = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 0.0f);

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);

    //--------------------------------------------
    
    reader.readFile(triangulation);


    verticesPerTriangle = 3;
    coordinatesPerVertex = 3;
    totalVertices = verticesPerTriangle * triangles.size();
    totalCoordinates = totalVertices * coordinatesPerVertex;

    vertices = new GLfloat[totalCoordinates];
    int currentIndex = 0;

    for (const Triangle& triangle : triangles)
    {
        // Iterate over each vertex of the triangle
        for (int i = 0; i < verticesPerTriangle; ++i)
        {
            // Get the index of the current vertex of the triangle
            int vertexIndex;
            if (i == 0)
                vertexIndex = triangle.v1();
            else if (i == 1)
                vertexIndex = triangle.v2();
            else
                vertexIndex = triangle.v3();

            // Append coordinates of the vertex to vertices array
            vertices[currentIndex++] = points[vertexIndex].x();
            vertices[currentIndex++] = points[vertexIndex].y();
            vertices[currentIndex++] = points[vertexIndex].z();
        }
    }
    size_t sizeOfVertices = totalCoordinates * sizeof(GLfloat);

    colors = new GLfloat[totalCoordinates];

    for (int i = 0; i < totalCoordinates; i += 3) {
        colors[i] = 1.0f;
        colors[i + 1] = 1.0f;
        colors[i + 2] = 0.0f;
    }


    //WaterPath ww;
    //HighestPoint pp;
    //path ff;
    //

    //vector<Point3D> waterPath;

    //
    //Point3D firstPoint;
    ///*firstPoint = pp.findHighestPoint(triangulation);
    //pp.findNextPoint(firstPoint, triangulation, 1.0, waterPath);*/
    //waterPath = ff.findpath(triangulation);
    //waterFlow = new GLfloat[waterPath.size()];
    //for (int i = 0; i < waterPath.size(); i += 3) {
    //    waterFlow[i] = waterPath[i].x();
    //    waterFlow[i + 1] = waterPath[i].y();
    //    waterFlow[i + 2] = waterPath[i].z();

    //}


    //colorsPath = new GLfloat[waterPath.size()];

    //for (int i = 0; i < waterPath.size(); i += 3) {
    //    colorsPath[i] = 0.0f;
    //    colorsPath[i + 1] = 0.0f;
    //    colorsPath[i + 2] = 1.0f;
    //}

}
void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
    {
        zoomOut();
    }
    else
    {
        zoomIn();
    }
}

void OpenGLWindow::zoomIn()
{
    scaleFactor /= 0.00001f;
    update();
}

void OpenGLWindow::zoomOut()
{
    scaleFactor *= 0.00001f;
    update();
}