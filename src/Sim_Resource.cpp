// Copyright (c) 2024 Krispin Davies
// SPDX-License-Identifier: BSD-3-Clause

#include "Sim_Resource.h"

#include "Simulation_Controls.h"

///////////////////////////////////////////////////////////////////////
// Drawing List Functions.
///////////////////////////////////////////////////////////////////////

GLuint kSim::drawList_Box()
{
  // On first use, create an identified for the OpenGL list.
  static const GLuint GEN_BOX_LIST = glGenLists(1);
  static bool GEN_BOX_LIST_Exists = false;

  if (GEN_BOX_LIST_Exists == false)
  {
    // Create new OpenGL list.
    glNewList(GEN_BOX_LIST, GL_COMPILE);

    // Draw floor cube.
    glBegin(GL_TRIANGLES);
    // Face 1
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);

    // Face 2
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // Face 3
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    // Face 4
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);

    // Face 5
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);

    // Face 6
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glEnd();
    glEndList();
    GEN_BOX_LIST_Exists = true;
  }

  // Return the number reference to the OpenGL list.
  return GEN_BOX_LIST;
}

GLuint kSim::drawList_BDY()
{
  // On first use, create an identified for the OpenGL list.
  static const GLuint CRICK_BDY_LIST = glGenLists(1);
  static bool CRICK_BDY_LIST_Exists = false;

  if (CRICK_BDY_LIST_Exists == false)
  {
    // Create new OpenGL list.
    glNewList(CRICK_BDY_LIST, GL_COMPILE);

    // Draw Cricket Body.
    glBegin(GL_QUADS);

    // Sensor Cage.
    glNormal3f(0.0, 0.0, 1.0);  // Top
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(0.0, 0.0, -1.0);  // Bottom
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(1.0, 0.0, 0.0);  // Front
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(-1.0, 0.0, 0.0);  // Back
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(0.0, 1.0, 0.0);  // Left
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(0.0, -1.0, 0.0);  // Right
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_CAGE_LENGTH / 2.0, -MODEL_BDY_CAGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);

    // Body Bridge.
    glNormal3f(0.0, 0.0, 1.0);  // Top
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(0.0, 0.0, -1.0);  // Bottom
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(1.0, 0.0, 0.0);  // Front
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glNormal3f(-1.0, 0.0, 0.0);  // Back
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);

    // Left Round Edge.
    for (int i = 0; i < MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glNormal3f(0.0, std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS),
                 std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) + MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS)
                   + MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS)
                   + MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) + MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
    }

    // Right Round Edge.
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glNormal3f(0.0, std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS),
                 std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) - MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS)
                   - MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS)
                   - MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) - MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
    }

    glEnd();  // GL_QUADS

    // Front Left
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, 0.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    for (int i = 0; i < MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS)
                   + MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    // Front Right
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, 0.0);
    glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glVertex3f(MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS)
                   - MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    // Back Left
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, 0.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, MODEL_BDY_BRIDGE_WIDTH / 2.0, -MODEL_BDY_HEIGHT / 2.0);
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i > 0; i--)
    {
      glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS)
                   + MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    // Back Right
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, 0.0);
    glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0, -MODEL_BDY_BRIDGE_WIDTH / 2.0, MODEL_BDY_HEIGHT / 2.0);
    for (int i = 2 * MODEL_GRAPHICS_ROUNDNESS; i > MODEL_GRAPHICS_ROUNDNESS; i--)
    {
      glVertex3f(-MODEL_BDY_BRIDGE_LENGTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::sin(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS)
                   - MODEL_BDY_BRIDGE_WIDTH / 2.0,
                 0.5 * MODEL_BDY_HEIGHT * std::cos(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    glEndList();
    CRICK_BDY_LIST_Exists = true;
  }

  // Return the number reference to the OpenGL list.
  return CRICK_BDY_LIST;
}

GLuint kSim::drawList_RFS()
{
  // On first use, create an identified for the OpenGL list.
  static const GLuint CRICK_RFS_LIST = glGenLists(1);
  static bool CRICK_RFS_LIST_Exists = false;

  if (CRICK_RFS_LIST_Exists == false)
  {
    // Create new OpenGL list.
    glNewList(CRICK_RFS_LIST, GL_COMPILE);

    // Draw Cricket Shoulder.
    glBegin(GL_QUADS);

    // Box Top.
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, MODEL_SHLD_BOX_WIDTH, MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, MODEL_SHLD_BOX_WIDTH, MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, 0.0, MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.0, MODEL_SHLD_BOX_HEIGHT / 2.0);

    // Box Bottom.
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, MODEL_SHLD_BOX_WIDTH, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.0, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, 0.0, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, MODEL_SHLD_BOX_WIDTH, -MODEL_SHLD_BOX_HEIGHT / 2.0);

    // Box Front.
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, MODEL_SHLD_BOX_WIDTH, MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.0, MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.0, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, MODEL_SHLD_BOX_WIDTH, -MODEL_SHLD_BOX_HEIGHT / 2.0);

    // Box Back.
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, MODEL_SHLD_BOX_WIDTH, MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, MODEL_SHLD_BOX_WIDTH, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, 0.0, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, 0.0, MODEL_SHLD_BOX_HEIGHT / 2.0);

    // Box Outside.
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, MODEL_SHLD_BOX_WIDTH, MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, MODEL_SHLD_BOX_WIDTH, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, MODEL_SHLD_BOX_WIDTH, -MODEL_SHLD_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH - MODEL_SHLD_BOX_LENGTH, MODEL_SHLD_BOX_WIDTH, MODEL_SHLD_BOX_HEIGHT / 2.0);

    // Cylinder.
    for (int i = 0; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glNormal3f(0.0, std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS),
                 std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.5 * MODEL_SHLD_CYL_DIA * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS),
                 0.5 * MODEL_SHLD_CYL_DIA * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.5 * MODEL_SHLD_CYL_DIA * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS),
                 0.5 * MODEL_SHLD_CYL_DIA * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.0, 0.5 * MODEL_SHLD_CYL_DIA * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS),
                 0.5 * MODEL_SHLD_CYL_DIA * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.0, 0.5 * MODEL_SHLD_CYL_DIA * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS),
                 0.5 * MODEL_SHLD_CYL_DIA * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
    }

    glEnd();

    // Front
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.0, 0.0);
    glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.0, MODEL_SHLD_CYL_DIA / 2.0);
    for (int i = 0; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glVertex3f(MODEL_SHLD_CYL_LENGTH, 0.5 * MODEL_SHLD_CYL_DIA * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS),
                 0.5 * MODEL_SHLD_CYL_DIA * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    glEndList();
    CRICK_RFS_LIST_Exists = true;
  }

  // Return the number reference to the OpenGL list.
  return CRICK_RFS_LIST;
}

GLuint kSim::drawList_RFP()
{
  // On first use, create an identified for the OpenGL list.
  static const GLuint CRICK_RFP_LIST = glGenLists(1);
  static bool CRICK_RFP_LIST_Exists = false;

  if (CRICK_RFP_LIST_Exists == false)
  {
    // Create new OpenGL list.
    glNewList(CRICK_RFP_LIST, GL_COMPILE);

    // Draw Cricket Proximal.
    glBegin(GL_QUADS);

    // Arm Top.
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_ARM_WIDTH, MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_PRX_ARM_WIDTH, MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, MODEL_PRX_ARM_HEIGHT / 2.0);

    // Arm Bottom.
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_ARM_WIDTH, -MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, -MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, -MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_PRX_ARM_WIDTH, -MODEL_PRX_ARM_HEIGHT / 2.0);

    // Arm Left.
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_ARM_WIDTH, MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_ARM_WIDTH, -MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_PRX_ARM_WIDTH, -MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_PRX_ARM_WIDTH, MODEL_PRX_ARM_HEIGHT / 2.0);

    // Arm Right.
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, -MODEL_PRX_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, -MODEL_PRX_ARM_HEIGHT / 2.0);

    // Box Top.
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, MODEL_PRX_BOX_WIDTH, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_BOX_WIDTH, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, 0.0, MODEL_PRX_BOX_HEIGHT / 2.0);

    // Box Bottom.
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, MODEL_PRX_BOX_WIDTH, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, 0.0, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_BOX_WIDTH, -MODEL_PRX_BOX_HEIGHT / 2.0);

    // Box Front.
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, MODEL_PRX_BOX_WIDTH, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, 0.0, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, 0.0, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, MODEL_PRX_BOX_WIDTH, -MODEL_PRX_BOX_HEIGHT / 2.0);

    // Box Back.
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_BOX_WIDTH, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_BOX_WIDTH, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, MODEL_PRX_BOX_HEIGHT / 2.0);

    // Box Left.
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, MODEL_PRX_BOX_WIDTH, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, MODEL_PRX_BOX_WIDTH, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_BOX_WIDTH, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, MODEL_PRX_BOX_WIDTH, MODEL_PRX_BOX_HEIGHT / 2.0);

    // Box Right.
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, 0.0, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH - MODEL_PRX_BOX_LENGTH, 0.0, -MODEL_PRX_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_PRX_ARM_LENGTH, 0.0, -MODEL_PRX_BOX_HEIGHT / 2.0);

    // Round edge.
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glNormal3f(std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_PRX_ARM_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), MODEL_PRX_ARM_WIDTH,
                 0.5 * MODEL_PRX_ARM_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_PRX_ARM_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 0.5 * MODEL_PRX_ARM_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_PRX_ARM_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 0.5 * MODEL_PRX_ARM_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_PRX_ARM_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_PRX_ARM_WIDTH,
                 0.5 * MODEL_PRX_ARM_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }

    glEnd();

    // Left Round Surface.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, MODEL_PRX_ARM_WIDTH, 0.0);
    glVertex3f(0.0, MODEL_PRX_ARM_WIDTH, -MODEL_PRX_ARM_HEIGHT / 2.0);
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glVertex3f(0.5 * MODEL_PRX_ARM_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_PRX_ARM_WIDTH,
                 0.5 * MODEL_PRX_ARM_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    glEndList();
    CRICK_RFP_LIST_Exists = true;
  }

  // Return the number reference to the OpenGL list.
  return CRICK_RFP_LIST;
}

GLuint kSim::drawList_RFD()
{
  // On first use, create an identified for the OpenGL list.
  static const GLuint CRICK_RFD_LIST = glGenLists(1);
  static bool CRICK_RFD_LIST_Exists = false;

  if (CRICK_RFD_LIST_Exists == false)
  {
    // Create new OpenGL list.
    glNewList(CRICK_RFD_LIST, GL_COMPILE);

    // Draw Cricket Distal.
    glBegin(GL_QUADS);

    // Arm Top.
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_DST_ARM_WIDTH, MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, 0.0, MODEL_DST_ARM_HEIGHT / 2.0);

    // Arm Bottom.
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, 0.0, -MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, -MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_DST_ARM_WIDTH, -MODEL_DST_ARM_HEIGHT / 2.0);

    // Arm Left.
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_DST_ARM_WIDTH, -MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_DST_ARM_WIDTH, MODEL_DST_ARM_HEIGHT / 2.0);

    // Arm Right.
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, 0.0, MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, -MODEL_DST_ARM_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, 0.0, -MODEL_DST_ARM_HEIGHT / 2.0);

    // Box Top.
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH,
               MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);

    // Box Bottom.
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH,
               -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);

    // Box Front.
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);

    // Box Back.
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH,
               -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH,
               MODEL_DST_BOX_HEIGHT / 2.0);

    // Box Left.
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);

    // Box Right.
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH, MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH,
               MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH - MODEL_DST_BOX_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH,
               -MODEL_DST_BOX_HEIGHT / 2.0);
    glVertex3f(MODEL_DST_ARM_LENGTH, MODEL_DST_ARM_WIDTH - MODEL_DST_BOX_WIDTH, -MODEL_DST_BOX_HEIGHT / 2.0);

    // Round edge.
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glNormal3f(std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_DST_ARM_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), MODEL_DST_ARM_WIDTH,
                 0.5 * MODEL_DST_ARM_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_DST_ARM_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 0.5 * MODEL_DST_ARM_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_DST_ARM_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 0.5 * MODEL_DST_ARM_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_DST_ARM_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_DST_ARM_WIDTH,
                 0.5 * MODEL_DST_ARM_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }

    glEnd();

    // Left Round Surface.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, MODEL_DST_ARM_WIDTH, 0.0);
    glVertex3f(0.0, MODEL_DST_ARM_WIDTH, -MODEL_DST_ARM_HEIGHT / 2.0);
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glVertex3f(0.5 * MODEL_DST_ARM_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_DST_ARM_WIDTH,
                 0.5 * MODEL_DST_ARM_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    glEndList();
    CRICK_RFD_LIST_Exists = true;
  }

  // Return the number reference to the OpenGL list.
  return CRICK_RFD_LIST;
}

GLuint kSim::drawList_RFT()
{
  // On first use, create an identified for the OpenGL list.
  static const GLuint CRICK_RFT_LIST = glGenLists(1);
  static bool CRICK_RFT_LIST_Exists = false;

  if (CRICK_RFT_LIST_Exists == false)
  {
    // Create new OpenGL list.
    glNewList(CRICK_RFT_LIST, GL_COMPILE);

    // Draw Cricket Distal.
    glBegin(GL_QUADS);

    // Top.
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(MODEL_TRK_LENGTH, 0.0, MODEL_TRK_HEIGHT / 2.0);

    // Bottom.
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(MODEL_TRK_LENGTH, 0.0, -MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, -MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0);

    // Left.
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0);

    // Right.
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(MODEL_TRK_LENGTH, 0.0, MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(0.0, 0.0, -MODEL_TRK_HEIGHT / 2.0);
    glVertex3f(MODEL_TRK_LENGTH, 0.0, -MODEL_TRK_HEIGHT / 2.0);

    // Front Arc.
    for (int i = 0; i < MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glNormal3f(std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH,
                 MODEL_TRK_WIDTH, 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH, 0.0,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH, 0.0,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH,
                 MODEL_TRK_WIDTH, 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }

    // Back Arc.
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glNormal3f(std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), MODEL_TRK_WIDTH,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_TRK_WIDTH,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }

    glEnd();

    // Front Left Round Surface.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, 0.0);
    glVertex3f(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0);
    for (int i = 0; i < MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH,
                 MODEL_TRK_WIDTH, 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    // Back Left Round Surface.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, MODEL_TRK_WIDTH, 0.0);
    glVertex3f(0.0, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0);
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
    {
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_TRK_WIDTH,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    // Front Right Round Surface.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(MODEL_TRK_LENGTH, 0.0, 0.0);
    glVertex3f(MODEL_TRK_LENGTH, 0.0, -MODEL_TRK_HEIGHT / 2.0);
    for (int i = MODEL_GRAPHICS_ROUNDNESS; i > 0; i--)
    {
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH, 0.0,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    // Back Right Round Surface.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, MODEL_TRK_HEIGHT / 2.0);
    for (int i = 2 * MODEL_GRAPHICS_ROUNDNESS; i > MODEL_GRAPHICS_ROUNDNESS; i--)
    {
      glVertex3f(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i - 1) / MODEL_GRAPHICS_ROUNDNESS));
    }
    glEnd();

    glEndList();
    CRICK_RFT_LIST_Exists = true;
  }

  // Return the number reference to the OpenGL list.
  return CRICK_RFT_LIST;
}

///////////////////////////////////////////////////////////////////////
// Environment Storage Structure
///////////////////////////////////////////////////////////////////////

kSim::Sim_Env_Struct::Sim_Env_Struct(double length_x,
                                     double width_y,
                                     double height_z,
                                     double max_dimension,
                                     double floor_thickness)
{
  // Determine the dimensions of the floor/ceiling arrays.
  m_length_x = length_x;
  m_cells_x = int(std::ceil(length_x / max_dimension));
  m_width_y = width_y;
  m_cells_y = int(std::ceil(width_y / max_dimension));
  m_height_z = height_z;
  floor_Array = new Sim_Env_Box[m_cells_x * m_cells_y];
  ceiling_Array = new Sim_Env_Box[m_cells_x * m_cells_y];

  double div_x = m_length_x / m_cells_x;
  double div_y = m_width_y / m_cells_y;

  // Initialise each floor and ceiling block to a standardised dimension.
  for (int i = 0; i < m_cells_x; i++)
  {
    for (int j = 0; j < m_cells_y; j++)
    {
      // Standard floor node.
      floor_Array[j * m_cells_x + i].m_low_x = i * div_x;
      floor_Array[j * m_cells_x + i].m_low_y = j * div_y;
      floor_Array[j * m_cells_x + i].m_low_z = 0;
      floor_Array[j * m_cells_x + i].m_high_x = (i + 1) * div_x;
      floor_Array[j * m_cells_x + i].m_high_y = (j + 1) * div_y;
      floor_Array[j * m_cells_x + i].m_high_z = floor_thickness;

      // Standard ceiling node.
      ceiling_Array[j * m_cells_x + i].m_low_x = i * div_x;
      ceiling_Array[j * m_cells_x + i].m_low_y = j * div_y;
      ceiling_Array[j * m_cells_x + i].m_low_z = m_height_z - floor_thickness;
      ceiling_Array[j * m_cells_x + i].m_high_x = (i + 1) * div_x;
      ceiling_Array[j * m_cells_x + i].m_high_y = (j + 1) * div_y;
      ceiling_Array[j * m_cells_x + i].m_high_z = m_height_z;

      // Deal with border regions.
      if (i == 0 || i == m_cells_x - 1 || j == 0 || j == m_cells_y - 1)
      {
        floor_Array[j * m_cells_x + i].m_high_z = 0.5 * m_height_z;
        ceiling_Array[j * m_cells_x + i].m_low_z = 0.5 * m_height_z;
      }

      // Build the OpenGL transformation arrays.
      floor_Array[j * m_cells_x + i].m_GLtrans = new GLfloat[16];
      floor_Array[j * m_cells_x + i].m_GLtrans[0] =
        floor_Array[j * m_cells_x + i].m_high_x - floor_Array[j * m_cells_x + i].m_low_x;
      floor_Array[j * m_cells_x + i].m_GLtrans[1] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[2] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[3] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[4] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[5] =
        floor_Array[j * m_cells_x + i].m_high_y - floor_Array[j * m_cells_x + i].m_low_y;
      floor_Array[j * m_cells_x + i].m_GLtrans[6] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[7] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[8] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[9] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[10] =
        floor_Array[j * m_cells_x + i].m_high_z - floor_Array[j * m_cells_x + i].m_low_z;
      floor_Array[j * m_cells_x + i].m_GLtrans[11] = 0;
      floor_Array[j * m_cells_x + i].m_GLtrans[12] =
        0.5 * (floor_Array[j * m_cells_x + i].m_high_x + floor_Array[j * m_cells_x + i].m_low_x);
      floor_Array[j * m_cells_x + i].m_GLtrans[13] =
        0.5 * (floor_Array[j * m_cells_x + i].m_high_y + floor_Array[j * m_cells_x + i].m_low_y);
      floor_Array[j * m_cells_x + i].m_GLtrans[14] =
        0.5 * (floor_Array[j * m_cells_x + i].m_high_z + floor_Array[j * m_cells_x + i].m_low_z);
      floor_Array[j * m_cells_x + i].m_GLtrans[15] = 1;

      ceiling_Array[j * m_cells_x + i].m_GLtrans = new GLfloat[16];
      ceiling_Array[j * m_cells_x + i].m_GLtrans[0] =
        ceiling_Array[j * m_cells_x + i].m_high_x - ceiling_Array[j * m_cells_x + i].m_low_x;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[1] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[2] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[3] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[4] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[5] =
        ceiling_Array[j * m_cells_x + i].m_high_y - ceiling_Array[j * m_cells_x + i].m_low_y;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[6] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[7] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[8] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[9] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[10] =
        ceiling_Array[j * m_cells_x + i].m_high_z - ceiling_Array[j * m_cells_x + i].m_low_z;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[11] = 0;
      ceiling_Array[j * m_cells_x + i].m_GLtrans[12] =
        0.5 * (ceiling_Array[j * m_cells_x + i].m_high_x + ceiling_Array[j * m_cells_x + i].m_low_x);
      ceiling_Array[j * m_cells_x + i].m_GLtrans[13] =
        0.5 * (ceiling_Array[j * m_cells_x + i].m_high_y + ceiling_Array[j * m_cells_x + i].m_low_y);
      ceiling_Array[j * m_cells_x + i].m_GLtrans[14] =
        0.5 * (ceiling_Array[j * m_cells_x + i].m_high_z + ceiling_Array[j * m_cells_x + i].m_low_z);
      ceiling_Array[j * m_cells_x + i].m_GLtrans[15] = 1;
    }
  }

  std::cout << " Floor specifications: " << m_length_x << ", " << m_width_y << ".\n";
}

kSim::Sim_Env_Struct::~Sim_Env_Struct()
{
  delete[] floor_Array;
  delete[] ceiling_Array;
}

kSim::Sim_Env_Struct::Sim_Env_Box& kSim::Sim_Env_Struct::getFloor(double x, double y)
{
  int target_cell_x = std::floor(x * m_cells_x / m_length_x);
  int target_cell_y = std::floor(y * m_cells_y / m_width_y);
  if (target_cell_x >= 0 && target_cell_x < m_cells_x && target_cell_y >= 0 && target_cell_y < m_cells_y)
    return floor_Array[target_cell_y * m_cells_x + target_cell_x];
  else
    throw Range_Error();
}

kSim::Sim_Env_Struct::Sim_Env_Box& kSim::Sim_Env_Struct::getCeiling(double x, double y)
{
  int target_cell_x = std::floor(x * m_cells_x / m_length_x);
  int target_cell_y = std::floor(y * m_cells_y / m_width_y);
  if (target_cell_x >= 0 && target_cell_x < m_cells_x && target_cell_y >= 0 && target_cell_y < m_cells_y)
    return ceiling_Array[target_cell_y * m_cells_x + target_cell_x];
  else
    throw Range_Error();
}

void kSim::Sim_Env_Struct::setFloor(double x, double y, double z)
{
  int target_cell_x = std::floor(x * m_cells_x / m_length_x);
  int target_cell_y = std::floor(y * m_cells_y / m_width_y);

  if (target_cell_x > 0 && target_cell_x < m_cells_x - 1 && target_cell_y > 0 && target_cell_y < m_cells_y - 1
      && z > 0.1)
  {
    int target_cell = target_cell_y * m_cells_x + target_cell_x;
    floor_Array[target_cell].m_high_z = z;

    // Build the OpenGL transformation arrays.
    floor_Array[target_cell].m_GLtrans = new GLfloat[16];
    floor_Array[target_cell].m_GLtrans[0] = floor_Array[target_cell].m_high_x - floor_Array[target_cell].m_low_x;
    floor_Array[target_cell].m_GLtrans[1] = 0;
    floor_Array[target_cell].m_GLtrans[2] = 0;
    floor_Array[target_cell].m_GLtrans[3] = 0;
    floor_Array[target_cell].m_GLtrans[4] = 0;
    floor_Array[target_cell].m_GLtrans[5] = floor_Array[target_cell].m_high_y - floor_Array[target_cell].m_low_y;
    floor_Array[target_cell].m_GLtrans[6] = 0;
    floor_Array[target_cell].m_GLtrans[7] = 0;
    floor_Array[target_cell].m_GLtrans[8] = 0;
    floor_Array[target_cell].m_GLtrans[9] = 0;
    floor_Array[target_cell].m_GLtrans[10] = floor_Array[target_cell].m_high_z - floor_Array[target_cell].m_low_z;
    floor_Array[target_cell].m_GLtrans[11] = 0;
    floor_Array[target_cell].m_GLtrans[12] =
      0.5 * (floor_Array[target_cell].m_high_x + floor_Array[target_cell].m_low_x);
    floor_Array[target_cell].m_GLtrans[13] =
      0.5 * (floor_Array[target_cell].m_high_y + floor_Array[target_cell].m_low_y);
    floor_Array[target_cell].m_GLtrans[14] =
      0.5 * (floor_Array[target_cell].m_high_z + floor_Array[target_cell].m_low_z);
    floor_Array[target_cell].m_GLtrans[15] = 1;

    return;
  }
}

void kSim::Sim_Env_Struct::setCeiling(double x, double y, double z)
{
  int target_cell_x = std::floor(x * m_cells_x / m_length_x);
  int target_cell_y = std::floor(y * m_cells_y / m_width_y);

  if (target_cell_x > 0 && target_cell_x < m_cells_x - 1 && target_cell_y > 0 && target_cell_y < m_cells_y - 1
      && z > 0.1)
  {
    int target_cell = target_cell_y * m_cells_x + target_cell_x;
    ceiling_Array[target_cell].m_low_z = z;

    // Build the OpenGL transformation arrays.
    ceiling_Array[target_cell].m_GLtrans = new GLfloat[16];
    ceiling_Array[target_cell].m_GLtrans[0] = ceiling_Array[target_cell].m_high_x - ceiling_Array[target_cell].m_low_x;
    ceiling_Array[target_cell].m_GLtrans[1] = 0;
    ceiling_Array[target_cell].m_GLtrans[2] = 0;
    ceiling_Array[target_cell].m_GLtrans[3] = 0;
    ceiling_Array[target_cell].m_GLtrans[4] = 0;
    ceiling_Array[target_cell].m_GLtrans[5] = ceiling_Array[target_cell].m_high_y - ceiling_Array[target_cell].m_low_y;
    ceiling_Array[target_cell].m_GLtrans[6] = 0;
    ceiling_Array[target_cell].m_GLtrans[7] = 0;
    ceiling_Array[target_cell].m_GLtrans[8] = 0;
    ceiling_Array[target_cell].m_GLtrans[9] = 0;
    ceiling_Array[target_cell].m_GLtrans[10] = ceiling_Array[target_cell].m_high_z - ceiling_Array[target_cell].m_low_z;
    ceiling_Array[target_cell].m_GLtrans[11] = 0;
    ceiling_Array[target_cell].m_GLtrans[12] =
      0.5 * (ceiling_Array[target_cell].m_high_x + ceiling_Array[target_cell].m_low_x);
    ceiling_Array[target_cell].m_GLtrans[13] =
      0.5 * (ceiling_Array[target_cell].m_high_y + ceiling_Array[target_cell].m_low_y);
    ceiling_Array[target_cell].m_GLtrans[14] =
      0.5 * (ceiling_Array[target_cell].m_high_z + ceiling_Array[target_cell].m_low_z);
    ceiling_Array[target_cell].m_GLtrans[15] = 1;
    return;
  }
}

///////////////////////////////////////////////////////////////////////
// Contact_List
///////////////////////////////////////////////////////////////////////

kSim::Contact_List::Contact_List(const Contact_List& source)
{
  m_size = source.get_size();
  m_counter = m_size;
  m_node_list = new Contact_Node[m_size];
  for (int i = 0; i < m_size; i++)
    m_node_list[i] = source(i);
}

void kSim::Contact_List::operator=(const Contact_List& source)
{
  if (this != &source)
  {
    if (m_node_list != NULL) delete[] m_node_list;
    m_size = source.get_size();
    m_counter = m_size;
    m_node_list = new Contact_Node[m_size];
    for (int i = 0; i < m_size; i++)
      m_node_list[i] = source(i);
  }
}

void kSim::Contact_List::add(const kMath::hVector& vertex, const kMath::hVector& normal, const double& surf_area)
{
  Contact_Node t_node;
  t_node.m_pos_x = vertex.get_val(0);
  t_node.m_pos_y = vertex.get_val(1);
  t_node.m_pos_z = vertex.get_val(2);
  t_node.m_norm_x = normal.get_val(0);
  t_node.m_norm_y = normal.get_val(1);
  t_node.m_norm_z = normal.get_val(2);
  t_node.m_surf_area = surf_area;

  if (m_counter == m_size)
  {
    if (m_node_list == NULL)
    {
      m_node_list = new Contact_Node[100];
      m_size = 100;
      m_counter = 0;
    }
    else
    {
      Contact_Node* temp = new Contact_Node[m_size + 100];
      for (int i = 0; i < m_size; i++)
        temp[i] = m_node_list[i];
      delete[] m_node_list;
      m_node_list = temp;
      m_size += 100;
    }
  }
  m_node_list[m_counter] = t_node;
  m_counter++;
}

void kSim::Contact_List::addTriangle(const kMath::hVector& v1,
                                     const kMath::hVector& v2,
                                     const kMath::hVector& v3,
                                     const kMath::hVector& normal)
{
  double t_area = sqrt(pow(v1.get_val(1) * v2.get_val(2) - v1.get_val(2) * v2.get_val(1), 2)
                       + pow(v1.get_val(0) * v2.get_val(2) - v1.get_val(2) * v2.get_val(0), 2)
                       + pow(v1.get_val(0) * v2.get_val(1) - v1.get_val(1) * v2.get_val(0), 2));
  double t_length_1 = sqrt(pow(v1.get_val(0) - v2.get_val(0), 2) + pow(v1.get_val(1) - v2.get_val(1), 2)
                           + pow(v1.get_val(2) - v2.get_val(2), 2));
  double t_length_2 = sqrt(pow(v1.get_val(0) - v3.get_val(0), 2) + pow(v1.get_val(1) - v3.get_val(1), 2)
                           + pow(v1.get_val(2) - v3.get_val(2), 2));
  double t_length_3 = sqrt(pow(v2.get_val(0) - v3.get_val(0), 2) + pow(v2.get_val(1) - v3.get_val(1), 2)
                           + pow(v2.get_val(2) - v3.get_val(2), 2));
  if (t_area > MODEL_MAX_CONTACT_AREA || t_length_1 > MODEL_MAX_CONTACT_SIDE_LENGTH
      || t_length_2 > MODEL_MAX_CONTACT_SIDE_LENGTH || t_length_3 > MODEL_MAX_CONTACT_SIDE_LENGTH)
  {
    this->addTriangle(v1, (v1 + v2) / 2.0, (v1 + v3) / 2.0, normal);
    this->addTriangle(v2, (v1 + v2) / 2.0, (v2 + v3) / 2.0, normal);
    this->addTriangle(v3, (v1 + v3) / 2.0, (v2 + v3) / 2.0, normal);
    this->addTriangle((v1 + v2) / 2.0, (v1 + v3) / 2.0, (v2 + v3) / 2.0, normal);
  }
  else
  {
    this->add((v1 + v2 + v3) / 3.0, normal, t_area);
  }
  return;
}

///////////////////////////////////////////////////////////////////////
// Simulation Containiner.
///////////////////////////////////////////////////////////////////////

kSim::Sim_Struct::Sim_Struct(double floor_x_dim,
                             double floor_y_dim,
                             double floor_z_dim,
                             double crick_pos_x,
                             double crick_pos_y,
                             double crick_pos_z)
  : m_environment(floor_x_dim, floor_y_dim, floor_z_dim, 0.1, 0.1)
  , m_cricket()
  , m_track_contacts()
  , m_sim_time(0)
  , m_last_vid_frame_time(0)
  , m_env_disp_mode(Environment)
  , m_crick_disp_mode(Graphics)
  , m_display_pitch(-0.0 * PI)
  , m_display_yaw(0.25 * PI)
  , m_display_zoom(0.8)
  , m_SR_image(false)
  , m_image_width(176)
  , m_image_height(144)
  , m_image_data(NULL)
  , m_cutoff_count(0)
{
  // Initialise the cricket's position.
  m_cricket.m_BDY.m_Pos_X = crick_pos_x;
  m_cricket.m_BDY.m_Pos_Y = crick_pos_y;
  m_cricket.m_BDY.m_Pos_Z = crick_pos_z;
  m_cricket.m_BDY.m_Pos_Quat1 = 1.0;

  // Initialise the environment layout.
  std::cout << " Preparing environment.\n";
  for (double x_outer = 0.15; x_outer <= m_environment.m_length_x - 0.15; x_outer += 0.1)
  {
    for (double y_outer = 0.15; y_outer <= m_environment.m_width_y - 0.15; y_outer += 0.1)
    {
      double floor_height = 0.1;  // + 0.1*(std::rand() % 100)/100.0;
      double ceiling_height = m_environment.m_height_z - 0.1 - 0.1 * (std::rand() % 100) / 100.0;
      m_environment.setFloor(x_outer, y_outer, floor_height);
      m_environment.setCeiling(x_outer, y_outer, ceiling_height);
    }
  }

  // Initialise the contact point lists.
  std::cout << " Building contact node lists.\n";
  this->Build_Contacts();

  // Inform the user that the initialization process has been completed.
  std::cout << " Setup complete.\n";
}

void kSim::Sim_Struct::Build_Contacts()
{
  /////////////////////////////////////
  // Define contact list for Tracks.
  /////////////////////////////////////

  // Top surface.
  m_track_contacts.addTriangle(
    kMath::h_Vec(0.0, 0.0, MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(MODEL_TRK_LENGTH, 0.0, MODEL_TRK_HEIGHT / 2.0),
    kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, 0.0, 1.0));
  m_track_contacts.addTriangle(
    kMath::h_Vec(0.0, 0.0, MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0),
    kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, 0.0, 1.0));

  // Bottom surface.
  m_track_contacts.addTriangle(
    kMath::h_Vec(0.0, 0.0, -MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(MODEL_TRK_LENGTH, 0.0, -MODEL_TRK_HEIGHT / 2.0),
    kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, 0.0, -1.0));
  m_track_contacts.addTriangle(
    kMath::h_Vec(0.0, 0.0, -MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0),
    kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, 0.0, -1.0));

  // Left surface.
  m_track_contacts.addTriangle(kMath::h_Vec(0.0, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0),
                               kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0),
                               kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0),
                               kMath::h_Vec(0.0, 1.0, 0.0));
  m_track_contacts.addTriangle(kMath::h_Vec(0.0, MODEL_TRK_WIDTH, -MODEL_TRK_HEIGHT / 2.0),
                               kMath::h_Vec(0.0, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0),
                               kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, MODEL_TRK_HEIGHT / 2.0),
                               kMath::h_Vec(0.0, 1.0, 0.0));

  // Right surface.
  m_track_contacts.addTriangle(
    kMath::h_Vec(0.0, 0.0, -MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(MODEL_TRK_LENGTH, 0.0, -MODEL_TRK_HEIGHT / 2.0),
    kMath::h_Vec(MODEL_TRK_LENGTH, 0.0, MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, -1.0, 0.0));
  m_track_contacts.addTriangle(
    kMath::h_Vec(0.0, 0.0, -MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, 0.0, MODEL_TRK_HEIGHT / 2.0),
    kMath::h_Vec(MODEL_TRK_LENGTH, 0.0, MODEL_TRK_HEIGHT / 2.0), kMath::h_Vec(0.0, -1.0, 0.0));

  // Front Arc.
  for (int i = 0; i < MODEL_GRAPHICS_ROUNDNESS; i++)
  {
    kMath::hVector norm = kMath::h_Vec(std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                                       std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v1 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH,
                   MODEL_TRK_WIDTH, 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v2 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH, 0.0,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v3 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH, 0.0,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v4 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH,
                   MODEL_TRK_WIDTH, 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    m_track_contacts.addTriangle(v1, v2, v3, norm);
    m_track_contacts.addTriangle(v1, v3, v4, norm);
  }

  // Back Arc.
  for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
  {
    kMath::hVector norm = kMath::h_Vec(std::sin(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                                       std::cos(PI * (i + 0.5) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v1 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), MODEL_TRK_WIDTH,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v2 = kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * i / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                                     0.5 * MODEL_TRK_HEIGHT * std::cos(PI * i / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v3 = kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                                     0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v4 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_TRK_WIDTH,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    m_track_contacts.addTriangle(v1, v2, v3, norm);
    m_track_contacts.addTriangle(v1, v3, v4, norm);
  }

  // Front Left Round Surface.
  for (int i = 0; i < MODEL_GRAPHICS_ROUNDNESS; i++)
  {
    kMath::hVector norm = kMath::h_Vec(0.0, 1.0, 0.0);
    kMath::hVector v1 = kMath::h_Vec(MODEL_TRK_LENGTH, MODEL_TRK_WIDTH, 0.0);
    kMath::hVector v2 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH,
                   MODEL_TRK_WIDTH, 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v3 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH,
                   MODEL_TRK_WIDTH, 0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    m_track_contacts.addTriangle(v1, v2, v3, norm);
  }

  // Front Right Round Surface.
  for (int i = 0; i < MODEL_GRAPHICS_ROUNDNESS; i++)
  {
    kMath::hVector norm = kMath::h_Vec(0.0, -1.0, 0.0);
    kMath::hVector v1 = kMath::h_Vec(MODEL_TRK_LENGTH, 0.0, 0.0);
    kMath::hVector v2 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH, 0.0,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v3 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS) + MODEL_TRK_LENGTH, 0.0,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    m_track_contacts.addTriangle(v1, v2, v3, norm);
  }

  // Back Left Round Surface.
  for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
  {
    kMath::hVector norm = kMath::h_Vec(0.0, 1.0, 0.0);
    kMath::hVector v1 = kMath::h_Vec(0.0, MODEL_TRK_WIDTH, 0.0);
    kMath::hVector v2 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i) / MODEL_GRAPHICS_ROUNDNESS), MODEL_TRK_WIDTH,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v3 =
      kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), MODEL_TRK_WIDTH,
                   0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    m_track_contacts.addTriangle(v1, v2, v3, norm);
  }

  // Back Right Round Surface.
  for (int i = MODEL_GRAPHICS_ROUNDNESS; i < 2 * MODEL_GRAPHICS_ROUNDNESS; i++)
  {
    kMath::hVector norm = kMath::h_Vec(0.0, -1.0, 0.0);
    kMath::hVector v1 = kMath::h_Vec(0.0, 0.0, 0.0);
    kMath::hVector v2 = kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                                     0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i) / MODEL_GRAPHICS_ROUNDNESS));
    kMath::hVector v3 = kMath::h_Vec(0.5 * MODEL_TRK_HEIGHT * std::sin(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS), 0.0,
                                     0.5 * MODEL_TRK_HEIGHT * std::cos(PI * (i + 1) / MODEL_GRAPHICS_ROUNDNESS));
    m_track_contacts.addTriangle(v1, v2, v3, norm);
  }

  std::cout << " Contact node lists complete.\n";
}

void kSim::Sim_Struct::Display()
{
  std::cout << "\nSystem Display\n";
  std::cout << "\nTime - " << m_sim_time << "\n";
  std::cout << "\nCricket Data - Body:\n   PosX = " << m_cricket.m_BDY.m_Pos_X << ", PosY = " << m_cricket.m_BDY.m_Pos_Y
            << ", PosZ = " << m_cricket.m_BDY.m_Pos_Z << ".\n";
  std::cout << "   VelX = " << m_cricket.m_BDY.m_Vel_X << ", VelY = " << m_cricket.m_BDY.m_Vel_Y
            << ", VelZ = " << m_cricket.m_BDY.m_Vel_Z << ".\n";
  std::cout << "   AccelX = " << m_cricket.m_BDY.m_Accel_X << ", AccelY = " << m_cricket.m_BDY.m_Accel_Y
            << ", AccelZ = " << m_cricket.m_BDY.m_Accel_Z << ".\n";
  std::cout << "   PosQ1 = " << m_cricket.m_BDY.m_Pos_Quat1 << ", PosQ2 = " << m_cricket.m_BDY.m_Pos_Quat2
            << ", PosQ3 = " << m_cricket.m_BDY.m_Pos_Quat3 << ", PosQ4 = " << m_cricket.m_BDY.m_Pos_Quat4 << ".\n";
  std::cout << "   VelQ1 = " << m_cricket.m_BDY.m_Vel_Quat1 << ", VelQ2 = " << m_cricket.m_BDY.m_Vel_Quat2
            << ", VelQ3 = " << m_cricket.m_BDY.m_Vel_Quat3 << ", VelQ4 = " << m_cricket.m_BDY.m_Vel_Quat4 << ".\n";
  std::cout << "   AccelQ1 = " << m_cricket.m_BDY.m_Accel_Quat1 << ", AccelQ2 = " << m_cricket.m_BDY.m_Accel_Quat2
            << ", AccelQ3 = " << m_cricket.m_BDY.m_Accel_Quat3 << ", AccelQ4 = " << m_cricket.m_BDY.m_Accel_Quat4
            << ".\n";
  std::cout << "   ExtFX = " << m_cricket.m_BDY.m_ExtF_X << ", ExtFY = " << m_cricket.m_BDY.m_ExtF_Y
            << ", ExtFZ = " << m_cricket.m_BDY.m_ExtF_Z << ".\n";
  std::cout << "   ExtMX = " << m_cricket.m_BDY.m_ExtM_X << ", ExtMY = " << m_cricket.m_BDY.m_ExtM_Y
            << ", ExtMZ = " << m_cricket.m_BDY.m_ExtM_Z << ".\n";
  std::cout << "\nCricket Data - CAM:\n   Pos = " << m_cricket.m_CAM.m_Joint_Angle
            << ", Vel = " << m_cricket.m_CAM.m_Joint_Vel << ", Accel = " << m_cricket.m_CAM.m_Joint_Accel << ".\n";
  std::cout << "   Torque = " << m_cricket.m_CAM.m_Joint_Torque << ",\n";
  std::cout << "   ExtFX = " << m_cricket.m_CAM.m_ExtF_X << ", ExtFY = " << m_cricket.m_CAM.m_ExtF_Y
            << ", ExtFZ = " << m_cricket.m_CAM.m_ExtF_Z << ".\n";
  std::cout << "   ExtMX = " << m_cricket.m_CAM.m_ExtM_X << ", ExtMY = " << m_cricket.m_CAM.m_ExtM_Y
            << ", ExtMZ = " << m_cricket.m_CAM.m_ExtM_Z << ".\n";
  std::cout << "\nCricket Data - RFT:\n   Pos = " << m_cricket.m_RFT.m_Joint_Angle
            << ", Vel = " << m_cricket.m_RFT.m_Joint_Vel << ", Accel = " << m_cricket.m_RFT.m_Joint_Accel << ".\n";
  std::cout << "   Torque = " << m_cricket.m_RFT.m_Joint_Torque << ",\n";
  std::cout << "   ExtFX = " << m_cricket.m_RFT.m_ExtF_X << ", ExtFY = " << m_cricket.m_RFT.m_ExtF_Y
            << ", ExtFZ = " << m_cricket.m_RFT.m_ExtF_Z << ".\n";
  std::cout << "   ExtMX = " << m_cricket.m_RFT.m_ExtM_X << ", ExtMY = " << m_cricket.m_RFT.m_ExtM_Y
            << ", ExtMZ = " << m_cricket.m_RFT.m_ExtM_Z << ".\n";
  std::cout << "\nCricket Data - LFT:\n   Pos = " << m_cricket.m_LFT.m_Joint_Angle
            << ", Vel = " << m_cricket.m_LFT.m_Joint_Vel << ", Accel = " << m_cricket.m_LFT.m_Joint_Accel << ".\n";
  std::cout << "   Torque = " << m_cricket.m_LFT.m_Joint_Torque << ",\n";
  std::cout << "   ExtFX = " << m_cricket.m_LFT.m_ExtF_X << ", ExtFY = " << m_cricket.m_LFT.m_ExtF_Y
            << ", ExtFZ = " << m_cricket.m_LFT.m_ExtF_Z << ".\n";
  std::cout << "   ExtMX = " << m_cricket.m_LFT.m_ExtM_X << ", ExtMY = " << m_cricket.m_LFT.m_ExtM_Y
            << ", ExtMZ = " << m_cricket.m_LFT.m_ExtM_Z << ".\n";
  std::cout << "\nCricket Data - RRT:\n   Pos = " << m_cricket.m_RRT.m_Joint_Angle
            << ", Vel = " << m_cricket.m_RRT.m_Joint_Vel << ", Accel = " << m_cricket.m_RRT.m_Joint_Accel << ".\n";
  std::cout << "   Torque = " << m_cricket.m_RRT.m_Joint_Torque << ",\n";
  std::cout << "   ExtFX = " << m_cricket.m_RRT.m_ExtF_X << ", ExtFY = " << m_cricket.m_RRT.m_ExtF_Y
            << ", ExtFZ = " << m_cricket.m_RRT.m_ExtF_Z << ".\n";
  std::cout << "   ExtMX = " << m_cricket.m_RRT.m_ExtM_X << ", ExtMY = " << m_cricket.m_RRT.m_ExtM_Y
            << ", ExtMZ = " << m_cricket.m_RRT.m_ExtM_Z << ".\n";
  std::cout << "\nCricket Data - LRT:\n   Pos = " << m_cricket.m_LRT.m_Joint_Angle
            << ", Vel = " << m_cricket.m_LRT.m_Joint_Vel << ", Accel = " << m_cricket.m_LRT.m_Joint_Accel << ".\n";
  std::cout << "   Torque = " << m_cricket.m_LRT.m_Joint_Torque << ",\n";
  std::cout << "   ExtFX = " << m_cricket.m_LRT.m_ExtF_X << ", ExtFY = " << m_cricket.m_LRT.m_ExtF_Y
            << ", ExtFZ = " << m_cricket.m_LRT.m_ExtF_Z << ".\n";
  std::cout << "   ExtMX = " << m_cricket.m_LRT.m_ExtM_X << ", ExtMY = " << m_cricket.m_LRT.m_ExtM_Y
            << ", ExtMZ = " << m_cricket.m_LRT.m_ExtM_Z << ".\n";
  std::cout << "\n";
}

void kSim::Sim_Struct::Sim_Step()
{
  // Perform explict Euler integration.
  {
    double max_accel = 0;
    double max_vel = 0;
    double time_step = 0;
    double scaling_factor = 1.0;

    // Determine externally imposed forces for initial state.
    try
    {
      this->Calc_ExtFM_RFT(m_cricket, max_vel);
      this->Calc_ExtFM_LFT(m_cricket, max_vel);
      this->Calc_ExtFM_RRT(m_cricket, max_vel);
      this->Calc_ExtFM_LRT(m_cricket, max_vel);
    }
    catch (Range_Error)
    {
      std::cout << "\n\n Throw on first. \n\n";
      throw;
    }

    // Determine the joint motor torques at initial moment.
    this->Calc_Torques(m_cricket);

    // Calculate joint accelerations caused by initial state.
    m_cricket.calcAccelQuat();

    // Determine maximum acceleration experienced in initial state.
    if (std::abs(m_cricket.m_BDY.m_Accel_X) > max_accel) max_accel = std::abs(m_cricket.m_BDY.m_Accel_X);
    if (std::abs(m_cricket.m_BDY.m_Accel_Y) > max_accel) max_accel = std::abs(m_cricket.m_BDY.m_Accel_Y);
    if (std::abs(m_cricket.m_BDY.m_Accel_Z) > max_accel) max_accel = std::abs(m_cricket.m_BDY.m_Accel_Z);
    if (std::abs(m_cricket.m_BDY.m_Accel_Quat1) > max_accel) max_accel = std::abs(m_cricket.m_BDY.m_Accel_Quat1);
    if (std::abs(m_cricket.m_BDY.m_Accel_Quat2) > max_accel) max_accel = std::abs(m_cricket.m_BDY.m_Accel_Quat2);
    if (std::abs(m_cricket.m_BDY.m_Accel_Quat3) > max_accel) max_accel = std::abs(m_cricket.m_BDY.m_Accel_Quat3);
    if (std::abs(m_cricket.m_BDY.m_Accel_Quat4) > max_accel) max_accel = std::abs(m_cricket.m_BDY.m_Accel_Quat4);
    if (std::abs(m_cricket.m_RFS.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RFS.m_Joint_Accel);
    if (std::abs(m_cricket.m_LFS.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LFS.m_Joint_Accel);
    if (std::abs(m_cricket.m_RRS.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RRS.m_Joint_Accel);
    if (std::abs(m_cricket.m_LRS.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LRS.m_Joint_Accel);
    if (std::abs(m_cricket.m_RFP.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RFP.m_Joint_Accel);
    if (std::abs(m_cricket.m_LFP.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LFP.m_Joint_Accel);
    if (std::abs(m_cricket.m_RRP.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RRP.m_Joint_Accel);
    if (std::abs(m_cricket.m_LRP.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LRP.m_Joint_Accel);
    if (std::abs(m_cricket.m_RFD.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RFD.m_Joint_Accel);
    if (std::abs(m_cricket.m_LFD.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LFD.m_Joint_Accel);
    if (std::abs(m_cricket.m_RRD.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RRD.m_Joint_Accel);
    if (std::abs(m_cricket.m_LRD.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LRD.m_Joint_Accel);
    if (std::abs(m_cricket.m_RFT.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RFT.m_Joint_Accel);
    if (std::abs(m_cricket.m_LFT.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LFT.m_Joint_Accel);
    if (std::abs(m_cricket.m_RRT.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_RRT.m_Joint_Accel);
    if (std::abs(m_cricket.m_LRT.m_Joint_Accel) > max_accel) max_accel = std::abs(m_cricket.m_LRT.m_Joint_Accel);

    // Scale time step for velocity of cricket contact points.
    if (MODEL_BASE_TIME_STEP * max_vel > MODEL_MAX_DISTANCE_STEP)
    {
      time_step = MODEL_MAX_DISTANCE_STEP / max_vel;
      scaling_factor = time_step / MODEL_BASE_TIME_STEP;
    }
    else
      time_step = MODEL_BASE_TIME_STEP;

    // Scale time step for acceleration produced from initial state.
    if (time_step * max_accel > MODEL_MAX_VELOCITY_STEP)
    {
      time_step = MODEL_MAX_VELOCITY_STEP / max_accel;
      scaling_factor = time_step / MODEL_BASE_TIME_STEP;
    }

    // Create temporary Cricket for testing the terminal state.
    kSim::Sim_Crick_Struct a1;

    // std::cout << "\n Max Vel: " << max_vel << " Max Accel:" << max_accel;

    while (true)
    {
      max_accel = 0;
      max_vel = 0;

      // Calculate the temporary cricket's terminal position/velocity.
      a1.m_BDY.m_Pos_X = m_cricket.m_BDY.m_Pos_X + m_cricket.m_BDY.m_Vel_X * time_step
                         + 0.5 * m_cricket.m_BDY.m_Accel_X * std::pow(time_step, 2);
      a1.m_BDY.m_Pos_Y = m_cricket.m_BDY.m_Pos_Y + m_cricket.m_BDY.m_Vel_Y * time_step
                         + 0.5 * m_cricket.m_BDY.m_Accel_Y * std::pow(time_step, 2);
      a1.m_BDY.m_Pos_Z = m_cricket.m_BDY.m_Pos_Z + m_cricket.m_BDY.m_Vel_Z * time_step
                         + 0.5 * m_cricket.m_BDY.m_Accel_Z * std::pow(time_step, 2);
      a1.m_BDY.m_Pos_Quat1 = m_cricket.m_BDY.m_Pos_Quat1 + m_cricket.m_BDY.m_Vel_Quat1 * time_step
                             + 0.5 * m_cricket.m_BDY.m_Accel_Quat1 * std::pow(time_step, 2);
      a1.m_BDY.m_Pos_Quat2 = m_cricket.m_BDY.m_Pos_Quat2 + m_cricket.m_BDY.m_Vel_Quat2 * time_step
                             + 0.5 * m_cricket.m_BDY.m_Accel_Quat2 * std::pow(time_step, 2);
      a1.m_BDY.m_Pos_Quat3 = m_cricket.m_BDY.m_Pos_Quat3 + m_cricket.m_BDY.m_Vel_Quat3 * time_step
                             + 0.5 * m_cricket.m_BDY.m_Accel_Quat3 * std::pow(time_step, 2);
      a1.m_BDY.m_Pos_Quat4 = m_cricket.m_BDY.m_Pos_Quat4 + m_cricket.m_BDY.m_Vel_Quat4 * time_step
                             + 0.5 * m_cricket.m_BDY.m_Accel_Quat4 * std::pow(time_step, 2);
      a1.m_BDY.m_Vel_X = m_cricket.m_BDY.m_Vel_X + m_cricket.m_BDY.m_Accel_X * time_step;
      a1.m_BDY.m_Vel_Y = m_cricket.m_BDY.m_Vel_Y + m_cricket.m_BDY.m_Accel_Y * time_step;
      a1.m_BDY.m_Vel_Z = m_cricket.m_BDY.m_Vel_Z + m_cricket.m_BDY.m_Accel_Z * time_step;
      a1.m_BDY.m_Vel_Quat1 = m_cricket.m_BDY.m_Vel_Quat1 + m_cricket.m_BDY.m_Accel_Quat1 * time_step;
      a1.m_BDY.m_Vel_Quat2 = m_cricket.m_BDY.m_Vel_Quat2 + m_cricket.m_BDY.m_Accel_Quat2 * time_step;
      a1.m_BDY.m_Vel_Quat3 = m_cricket.m_BDY.m_Vel_Quat3 + m_cricket.m_BDY.m_Accel_Quat3 * time_step;
      a1.m_BDY.m_Vel_Quat4 = m_cricket.m_BDY.m_Vel_Quat4 + m_cricket.m_BDY.m_Accel_Quat4 * time_step;
      a1.m_RFS.m_Joint_Angle = m_cricket.m_RFS.m_Joint_Angle + m_cricket.m_RFS.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RFS.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RFS.m_Joint_Vel = m_cricket.m_RFS.m_Joint_Vel + m_cricket.m_RFS.m_Joint_Accel * time_step;
      a1.m_LFS.m_Joint_Angle = m_cricket.m_LFS.m_Joint_Angle + m_cricket.m_LFS.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LFS.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LFS.m_Joint_Vel = m_cricket.m_LFS.m_Joint_Vel + m_cricket.m_LFS.m_Joint_Accel * time_step;
      a1.m_RRS.m_Joint_Angle = m_cricket.m_RRS.m_Joint_Angle + m_cricket.m_RRS.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RRS.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RRS.m_Joint_Vel = m_cricket.m_RRS.m_Joint_Vel + m_cricket.m_RRS.m_Joint_Accel * time_step;
      a1.m_LRS.m_Joint_Angle = m_cricket.m_LRS.m_Joint_Angle + m_cricket.m_LRS.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LRS.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LRS.m_Joint_Vel = m_cricket.m_LRS.m_Joint_Vel + m_cricket.m_LRS.m_Joint_Accel * time_step;
      a1.m_RFP.m_Joint_Angle = m_cricket.m_RFP.m_Joint_Angle + m_cricket.m_RFP.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RFP.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RFP.m_Joint_Vel = m_cricket.m_RFP.m_Joint_Vel + m_cricket.m_RFP.m_Joint_Accel * time_step;
      a1.m_LFP.m_Joint_Angle = m_cricket.m_LFP.m_Joint_Angle + m_cricket.m_LFP.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LFP.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LFP.m_Joint_Vel = m_cricket.m_LFP.m_Joint_Vel + m_cricket.m_LFP.m_Joint_Accel * time_step;
      a1.m_RRP.m_Joint_Angle = m_cricket.m_RRP.m_Joint_Angle + m_cricket.m_RRP.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RRP.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RRP.m_Joint_Vel = m_cricket.m_RRP.m_Joint_Vel + m_cricket.m_RRP.m_Joint_Accel * time_step;
      a1.m_LRP.m_Joint_Angle = m_cricket.m_LRP.m_Joint_Angle + m_cricket.m_LRP.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LRP.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LRP.m_Joint_Vel = m_cricket.m_LRP.m_Joint_Vel + m_cricket.m_LRP.m_Joint_Accel * time_step;
      a1.m_RFD.m_Joint_Angle = m_cricket.m_RFD.m_Joint_Angle + m_cricket.m_RFD.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RFD.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RFD.m_Joint_Vel = m_cricket.m_RFD.m_Joint_Vel + m_cricket.m_RFD.m_Joint_Accel * time_step;
      a1.m_LFD.m_Joint_Angle = m_cricket.m_LFD.m_Joint_Angle + m_cricket.m_LFD.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LFD.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LFD.m_Joint_Vel = m_cricket.m_LFD.m_Joint_Vel + m_cricket.m_LFD.m_Joint_Accel * time_step;
      a1.m_RRD.m_Joint_Angle = m_cricket.m_RRD.m_Joint_Angle + m_cricket.m_RRD.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RRD.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RRD.m_Joint_Vel = m_cricket.m_RRD.m_Joint_Vel + m_cricket.m_RRD.m_Joint_Accel * time_step;
      a1.m_LRD.m_Joint_Angle = m_cricket.m_LRD.m_Joint_Angle + m_cricket.m_LRD.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LRD.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LRD.m_Joint_Vel = m_cricket.m_LRD.m_Joint_Vel + m_cricket.m_LRD.m_Joint_Accel * time_step;
      a1.m_RFT.m_Joint_Angle = m_cricket.m_RFT.m_Joint_Angle + m_cricket.m_RFT.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RFT.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RFT.m_Joint_Vel = m_cricket.m_RFT.m_Joint_Vel + m_cricket.m_RFT.m_Joint_Accel * time_step;
      a1.m_LFT.m_Joint_Angle = m_cricket.m_LFT.m_Joint_Angle + m_cricket.m_LFT.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LFT.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LFT.m_Joint_Vel = m_cricket.m_LFT.m_Joint_Vel + m_cricket.m_LFT.m_Joint_Accel * time_step;
      a1.m_RRT.m_Joint_Angle = m_cricket.m_RRT.m_Joint_Angle + m_cricket.m_RRT.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_RRT.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_RRT.m_Joint_Vel = m_cricket.m_RRT.m_Joint_Vel + m_cricket.m_RRT.m_Joint_Accel * time_step;
      a1.m_LRT.m_Joint_Angle = m_cricket.m_LRT.m_Joint_Angle + m_cricket.m_LRT.m_Joint_Vel * time_step
                               + 0.5 * m_cricket.m_LRT.m_Joint_Accel * std::pow(time_step, 2);
      a1.m_LRT.m_Joint_Vel = m_cricket.m_LRT.m_Joint_Vel + m_cricket.m_LRT.m_Joint_Accel * time_step;

      // Normalize the quaternion.
      double t_quat_scale_factor = sqrt(pow(a1.m_BDY.m_Pos_Quat1, 2) + pow(a1.m_BDY.m_Pos_Quat2, 2)
                                        + pow(a1.m_BDY.m_Pos_Quat3, 2) + pow(a1.m_BDY.m_Pos_Quat4, 2));
      a1.m_BDY.m_Pos_Quat1 /= t_quat_scale_factor;
      a1.m_BDY.m_Pos_Quat2 /= t_quat_scale_factor;
      a1.m_BDY.m_Pos_Quat3 /= t_quat_scale_factor;
      a1.m_BDY.m_Pos_Quat4 /= t_quat_scale_factor;

      // Determine externally imposed forces in terminal state.
      try
      {
        this->Calc_ExtFM_RFT(a1, max_vel);
        this->Calc_ExtFM_LFT(a1, max_vel);
        this->Calc_ExtFM_RRT(a1, max_vel);
        this->Calc_ExtFM_LRT(a1, max_vel);
      }
      catch (Range_Error)
      {
        std::cout << "\n Scaling due to range error.";
        time_step = MODEL_BASE_TIME_STEP * scaling_factor;
        scaling_factor /= 2.0;
        continue;
      }

      // Determine the joint motor torques at initial moment.
      this->Calc_Torques(a1);

      // Calculate joint accelerations caused by terminal state.
      a1.calcAccelQuat();

      // Determine maximum acceleration experienced in initial state.
      if (std::abs(a1.m_BDY.m_Accel_X) > max_accel) max_accel = std::abs(a1.m_BDY.m_Accel_X);
      if (std::abs(a1.m_BDY.m_Accel_Y) > max_accel) max_accel = std::abs(a1.m_BDY.m_Accel_Y);
      if (std::abs(a1.m_BDY.m_Accel_Z) > max_accel) max_accel = std::abs(a1.m_BDY.m_Accel_Z);
      if (std::abs(a1.m_BDY.m_Accel_Quat1) > max_accel) max_accel = std::abs(a1.m_BDY.m_Accel_Quat1);
      if (std::abs(a1.m_BDY.m_Accel_Quat2) > max_accel) max_accel = std::abs(a1.m_BDY.m_Accel_Quat2);
      if (std::abs(a1.m_BDY.m_Accel_Quat3) > max_accel) max_accel = std::abs(a1.m_BDY.m_Accel_Quat3);
      if (std::abs(a1.m_BDY.m_Accel_Quat4) > max_accel) max_accel = std::abs(a1.m_BDY.m_Accel_Quat4);
      if (std::abs(a1.m_RFS.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RFS.m_Joint_Accel);
      if (std::abs(a1.m_LFS.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LFS.m_Joint_Accel);
      if (std::abs(a1.m_RRS.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RRS.m_Joint_Accel);
      if (std::abs(a1.m_LRS.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LRS.m_Joint_Accel);
      if (std::abs(a1.m_RFP.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RFP.m_Joint_Accel);
      if (std::abs(a1.m_LFP.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LFP.m_Joint_Accel);
      if (std::abs(a1.m_RRP.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RRP.m_Joint_Accel);
      if (std::abs(a1.m_LRP.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LRP.m_Joint_Accel);
      if (std::abs(a1.m_RFD.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RFD.m_Joint_Accel);
      if (std::abs(a1.m_LFD.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LFD.m_Joint_Accel);
      if (std::abs(a1.m_RRD.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RRD.m_Joint_Accel);
      if (std::abs(a1.m_LRD.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LRD.m_Joint_Accel);
      if (std::abs(a1.m_RFT.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RFT.m_Joint_Accel);
      if (std::abs(a1.m_LFT.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LFT.m_Joint_Accel);
      if (std::abs(a1.m_RRT.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_RRT.m_Joint_Accel);
      if (std::abs(a1.m_LRT.m_Joint_Accel) > max_accel) max_accel = std::abs(a1.m_LRT.m_Joint_Accel);

      // Scale time step for acceleration or velocity and recompute if
      // necessary.
      if (time_step * max_accel > MODEL_MAX_VELOCITY_STEP * std::exp(-0.5 * std::log10(max_accel))
          || time_step * max_vel > MODEL_MAX_DISTANCE_STEP)
      {
        time_step = MODEL_BASE_TIME_STEP * scaling_factor;
        scaling_factor /= 2.0;
        continue;
      }

      // If we reached this point, things ran as planned, so we can break out of
      // the loop.
      break;
    }

    this->Display();

    // Update the simulation's version of the Cricket.
    m_cricket = a1;

    // Increment simulation time.
    m_sim_time += time_step;
  }

  // throw Range_Error();
}

void kSim::Sim_Struct::Calc_Torques(kSim::Sim_Crick_Struct& In_Crick)
{
  double torque_max = 24.5;
  double vel_p_gain = -50.0, pos_p_gain = -5000.0;
  double target_vel_RFT = 0.0, target_pos_RFT = 0.0;
  double target_vel_LFT = 0.0, target_pos_LFT = 0.0;
  double target_vel_RRT = 0.0, target_pos_RRT = PI;
  double target_vel_LRT = 0.0, target_pos_LRT = PI;

  // = = = = = = = = = = = =
  // RFT
  // = = = = = = = = = = = =

  // Select Motor Torque.
  In_Crick.m_RFT.m_Joint_Torque = vel_p_gain * (In_Crick.m_RFT.m_Joint_Vel - target_vel_RFT)
                                  + pos_p_gain * (In_Crick.m_RFT.m_Joint_Angle - target_pos_RFT);
  if (std::abs(In_Crick.m_RFT.m_Joint_Torque) > torque_max)
    In_Crick.m_RFT.m_Joint_Torque =
      torque_max * (In_Crick.m_RFT.m_Joint_Torque / std::abs(In_Crick.m_RFT.m_Joint_Torque));
  // Deal with joint backforcing.
  if (std::abs(In_Crick.m_RFT.m_ExtM_Y) > std::abs(In_Crick.m_RFT.m_Joint_Torque))
  {
    if ((In_Crick.m_RFT.m_Joint_Torque < 0 ? -1 : 1) == (In_Crick.m_RFT.m_ExtM_Y < 0 ? -1 : 1))
      In_Crick.m_RFT.m_Joint_Torque = In_Crick.m_RFT.m_Joint_Torque - In_Crick.m_RFT.m_ExtM_Y;
    else
      In_Crick.m_RFT.m_Joint_Torque = -In_Crick.m_RFT.m_ExtM_Y;
  }
  // Determine motor friction Torque.
  if (std::abs(In_Crick.m_RFT.m_Joint_Vel) > 15.08)
    In_Crick.m_RFT.m_Joint_Torque +=
      (30.6 - 2.03 * std::abs(In_Crick.m_RFT.m_Joint_Vel)) * (In_Crick.m_RFT.m_Joint_Vel < 0 ? -1 : 1);

  // = = = = = = = = = = = =
  // LFT
  // = = = = = = = = = = = =

  // Select Motor Torque.
  In_Crick.m_LFT.m_Joint_Torque = vel_p_gain * (In_Crick.m_LFT.m_Joint_Vel - target_vel_LFT)
                                  + pos_p_gain * (In_Crick.m_LFT.m_Joint_Angle - target_pos_LFT);
  if (std::abs(In_Crick.m_LFT.m_Joint_Torque) > torque_max)
    In_Crick.m_LFT.m_Joint_Torque =
      torque_max * (In_Crick.m_LFT.m_Joint_Torque / std::abs(In_Crick.m_LFT.m_Joint_Torque));
  // Deal with joint backforcing.
  if (std::abs(In_Crick.m_LFT.m_ExtM_Y) > std::abs(In_Crick.m_LFT.m_Joint_Torque))
  {
    if ((In_Crick.m_LFT.m_Joint_Torque < 0 ? -1 : 1) == (In_Crick.m_LFT.m_ExtM_Y < 0 ? -1 : 1))
      In_Crick.m_LFT.m_Joint_Torque = In_Crick.m_LFT.m_Joint_Torque - In_Crick.m_LFT.m_ExtM_Y;
    else
      In_Crick.m_LFT.m_Joint_Torque = -In_Crick.m_LFT.m_ExtM_Y;
  }
  // Determine motor friction Torque.
  if (std::abs(In_Crick.m_LFT.m_Joint_Vel) > 15.08)
    In_Crick.m_LFT.m_Joint_Torque +=
      (30.6 - 2.03 * std::abs(In_Crick.m_LFT.m_Joint_Vel)) * (In_Crick.m_LFT.m_Joint_Vel < 0 ? -1 : 1);

  // = = = = = = = = = = = =
  // RRT
  // = = = = = = = = = = = =

  // Select Motor Torque.
  In_Crick.m_RRT.m_Joint_Torque = vel_p_gain * (In_Crick.m_RRT.m_Joint_Vel - target_vel_RRT)
                                  + pos_p_gain * (In_Crick.m_RRT.m_Joint_Angle - target_pos_RRT);
  if (std::abs(In_Crick.m_RRT.m_Joint_Torque) > torque_max)
    In_Crick.m_RRT.m_Joint_Torque =
      torque_max * (In_Crick.m_RRT.m_Joint_Torque / std::abs(In_Crick.m_RRT.m_Joint_Torque));
  // Deal with joint backforcing.
  if (std::abs(In_Crick.m_RRT.m_ExtM_Y) > std::abs(In_Crick.m_RRT.m_Joint_Torque))
  {
    if ((In_Crick.m_RRT.m_Joint_Torque < 0 ? -1 : 1) == (In_Crick.m_RRT.m_ExtM_Y < 0 ? -1 : 1))
      In_Crick.m_RRT.m_Joint_Torque = In_Crick.m_RRT.m_Joint_Torque - In_Crick.m_RRT.m_ExtM_Y;
    else
      In_Crick.m_RRT.m_Joint_Torque = -In_Crick.m_RRT.m_ExtM_Y;
  }
  // Determine motor friction Torque.
  if (std::abs(In_Crick.m_RRT.m_Joint_Vel) > 15.08)
    In_Crick.m_RRT.m_Joint_Torque +=
      (30.6 - 2.03 * std::abs(In_Crick.m_RRT.m_Joint_Vel)) * (In_Crick.m_RRT.m_Joint_Vel < 0 ? -1 : 1);

  // = = = = = = = = = = = =
  // LRT
  // = = = = = = = = = = = =

  // Select Motor Torque.
  In_Crick.m_LRT.m_Joint_Torque = vel_p_gain * (In_Crick.m_LRT.m_Joint_Vel - target_vel_LRT)
                                  + pos_p_gain * (In_Crick.m_LRT.m_Joint_Angle - target_pos_LRT);
  if (std::abs(In_Crick.m_LRT.m_Joint_Torque) > torque_max)
    In_Crick.m_LRT.m_Joint_Torque =
      torque_max * (In_Crick.m_LRT.m_Joint_Torque / std::abs(In_Crick.m_LRT.m_Joint_Torque));
  // Deal with joint backforcing.
  if (std::abs(In_Crick.m_LRT.m_ExtM_Y) > std::abs(In_Crick.m_LRT.m_Joint_Torque))
  {
    if ((In_Crick.m_LRT.m_Joint_Torque < 0 ? -1 : 1) == (In_Crick.m_LRT.m_ExtM_Y < 0 ? -1 : 1))
      In_Crick.m_LRT.m_Joint_Torque = In_Crick.m_LRT.m_Joint_Torque - In_Crick.m_LRT.m_ExtM_Y;
    else
      In_Crick.m_LRT.m_Joint_Torque = -In_Crick.m_LRT.m_ExtM_Y;
  }
  // Determine motor friction Torque.
  if (std::abs(In_Crick.m_LRT.m_Joint_Vel) > 15.08)
    In_Crick.m_LRT.m_Joint_Torque +=
      (30.6 - 2.03 * std::abs(In_Crick.m_LRT.m_Joint_Vel)) * (In_Crick.m_LRT.m_Joint_Vel < 0 ? -1 : 1);
}

kMath::hVector kSim::Sim_Struct::Calc_Force(kSim::Sim_Env_Struct::Sim_Env_Box curr_floor_node,
                                            kMath::hVector contact_node_pos,
                                            kMath::hVector contact_node_vel,
                                            kMath::hVector contact_node_normal,
                                            double contact_area)
{
  kMath::hVector force_global = kMath::h_Vec(0, 0, 0);

  // Calculate spring/damping force.
  {
    // Determine how far the contact node has penetrated the environmental
    // object.
    double penetration = 0.002;  // This limits the penetration to some reasonable amount, helps
                                 // with sideways motion!
    double temp = 0;

    // Check X.
    if (contact_node_normal(0) != 0)
    {
      if (contact_node_normal(0) > 0)
        temp = (curr_floor_node.m_high_x - contact_node_pos(0)) / contact_node_normal(0);
      else
        temp = (curr_floor_node.m_low_x - contact_node_pos(0))
               / contact_node_normal(0);  // Both top and bottom are negative hence
                                          // they will give a positive penetration.
      if (temp < penetration) penetration = temp;
    }

    // Check Y.
    if (contact_node_normal(1) != 0)
    {
      if (contact_node_normal(1) > 0)
        temp = (curr_floor_node.m_high_y - contact_node_pos(1)) / contact_node_normal(1);
      else
        temp = (curr_floor_node.m_low_y - contact_node_pos(1))
               / contact_node_normal(1);  // Both top and bottom are negative hence
                                          // they will give a positive penetration.
      if (temp < penetration) penetration = temp;
    }

    // Check Z.
    if (contact_node_normal(2) != 0)
    {
      if (contact_node_normal(2) > 0)
        temp = (curr_floor_node.m_high_z - contact_node_pos(2)) / contact_node_normal(2);
      else
        temp = (curr_floor_node.m_low_z - contact_node_pos(2))
               / contact_node_normal(2);  // Both top and bottom are negative hence
                                          // they will give a positive penetration.
      if (temp < penetration) penetration = temp;
    }

    // Safety test, check for ridiculous penetration.
    if (penetration > 10)
    {
      std::cout << "\n\n Extreme BDY penetration warning! " << penetration;
      std::cout << "\n Contact node position: " << contact_node_pos(0) << ", " << contact_node_pos(1) << ", "
                << contact_node_pos(2);
      std::cout << "\n Contact node normal: " << contact_node_normal(0) << ", " << contact_node_normal(1) << ", "
                << contact_node_normal(2);
      std::cout << "\n Floor node highs: " << curr_floor_node.m_high_x << ", " << curr_floor_node.m_high_y << ", "
                << curr_floor_node.m_high_z;
      std::cout << "\n Floor node lows:  " << curr_floor_node.m_low_x << ", " << curr_floor_node.m_low_y << ", "
                << curr_floor_node.m_low_z;
    }
    if (penetration < 0) std::cout << "\n\n Negative BDY penetration warning!";

    // SPRING

    // Calculate spring force.
    force_global += -1 * penetration * MODEL_ENV_SPRING_COEFF * contact_node_normal;

    // DAMPING

    // Determine velocity parallel to force normal.
    kMath::hVector parallel_vel = kMath::dot(contact_node_vel, contact_node_normal) * contact_node_normal;

    // Include damping force into global force for node.
    force_global += -1 * penetration * MODEL_ENV_DAMPING_COEFF * parallel_vel;
  }

  // Check that the damping force has not produced a normal force which 'pulls'
  // out from the surface.
  if (kMath::dot(force_global, contact_node_normal) > 0) force_global = kMath::h_Vec(0, 0, 0);

  // Scale the force by the unit area of the contact node.
  force_global = force_global * contact_area;

  // Calculate frictional force.
  {
    // Determine velocity perpendicular to force normal.
    kMath::hVector perpend_vel = contact_node_vel - dot(contact_node_vel, contact_node_normal) * contact_node_normal;

    // Determine frictional coefficient.
    double fric_coeff;
    if (perpend_vel.mag() > 0.01)
      fric_coeff = MODEL_ENV_FRICT_COEFF_DYNAMIC;
    else
      fric_coeff = MODEL_ENV_FRICT_COEFF_STATIC;

    // Normalize the perpendicular velocity to get direction of action of
    // friction force.
    perpend_vel.normalize();

    // Include friction force into global force for node.
    force_global += -fric_coeff * force_global.mag() * perpend_vel;
  }

  // Return the cumulative force in the global frame of reference.
  return force_global;
}

void kSim::Sim_Struct::Calc_ExtFM_RFT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel)
{
  // Pre-allocate memory for calculations used in the system, this saves
  // re-allocation time.
  kSim::Contact_List::Contact_Node curr_contact_node;
  kMath::hVector contact_node_pos;
  kMath::hVector contact_node_vel;
  kMath::hVector contact_node_normal;
  kSim::Sim_Env_Struct::Sim_Env_Box curr_floor_node;
  kMath::hVector contact_force_global;
  kMath::hVector contact_force_local;

  In_Crick.m_RFT.m_ExtF_X = 0;
  In_Crick.m_RFT.m_ExtF_Y = 0;
  In_Crick.m_RFT.m_ExtF_Z = 0;
  In_Crick.m_RFT.m_ExtM_X = 0;
  In_Crick.m_RFT.m_ExtM_Y = 0;
  In_Crick.m_RFT.m_ExtM_Z = 0;

  // Cycle through each of the contact nodes in the list.
  for (int i = 0; i < m_track_contacts.get_size(); i++)
  {
    curr_contact_node = m_track_contacts(i);
    curr_contact_node.m_pos_y *= -1.0;   // Only for tracks on the right hand side.
    curr_contact_node.m_norm_y *= -1.0;  // Only for tracks on the right hand side.

    // Calculate the Global position and velocity of the contact node.
    contact_node_vel = kMath::h_Vec(0, 0, 0);
    contact_node_pos = kMath::h_Point(curr_contact_node.m_pos_x, curr_contact_node.m_pos_y, curr_contact_node.m_pos_z);

    contact_node_vel =
      kMath::h_VRoty(In_Crick.m_RFT.m_Joint_Angle, In_Crick.m_RFT.m_Joint_Vel, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_Roty(In_Crick.m_RFT.m_Joint_Angle);

    contact_node_pos += kMath::h_Vec(MODEL_RFT_Origin_X, MODEL_RFT_Origin_Y, MODEL_RFT_Origin_Z);

    contact_node_vel =
      kMath::h_VRotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                        In_Crick.m_BDY.m_Pos_Quat4, In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                        In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                                         In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4);

    contact_node_vel += kMath::h_Vec(In_Crick.m_BDY.m_Vel_X, In_Crick.m_BDY.m_Vel_Y, In_Crick.m_BDY.m_Vel_Z);
    contact_node_pos += kMath::h_Vec(In_Crick.m_BDY.m_Pos_X, In_Crick.m_BDY.m_Pos_Y, In_Crick.m_BDY.m_Pos_Z);

    // Determine maximum velocity.
    if (contact_node_vel.mag() > max_vel) max_vel = contact_node_vel.mag();

    // Test to see if this space is occupied by floor.
    curr_floor_node = m_environment.getFloor(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_RFT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_RFT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_RFT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_RFT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_RFT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_RFT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_RFT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_RFT_COG_Z) * contact_force_local(1);
      In_Crick.m_RFT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_RFT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_RFT_COG_Z) * contact_force_local(0);
      In_Crick.m_RFT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_RFT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_RFT_COG_Y) * contact_force_local(0);
    }

    // Test to see if this space is occupied by ceiling.
    curr_floor_node = m_environment.getCeiling(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_RFT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_RFT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_RFT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_RFT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_RFT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_RFT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_RFT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_RFT_COG_Z) * contact_force_local(1);
      In_Crick.m_RFT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_RFT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_RFT_COG_Z) * contact_force_local(0);
      In_Crick.m_RFT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_RFT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_RFT_COG_Y) * contact_force_local(0);
    }
  }
}

void kSim::Sim_Struct::Calc_ExtFM_LFT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel)
{
  // Pre-allocate memory for calculations used in the system, this saves
  // re-allocation time.
  kSim::Contact_List::Contact_Node curr_contact_node;
  kMath::hVector contact_node_pos;
  kMath::hVector contact_node_vel;
  kMath::hVector contact_node_normal;
  kSim::Sim_Env_Struct::Sim_Env_Box curr_floor_node;
  kMath::hVector contact_force_global;
  kMath::hVector contact_force_local;

  In_Crick.m_LFT.m_ExtF_X = 0;
  In_Crick.m_LFT.m_ExtF_Y = 0;
  In_Crick.m_LFT.m_ExtF_Z = 0;
  In_Crick.m_LFT.m_ExtM_X = 0;
  In_Crick.m_LFT.m_ExtM_Y = 0;
  In_Crick.m_LFT.m_ExtM_Z = 0;

  // Cycle through each of the contact nodes in the list.
  for (int i = 0; i < m_track_contacts.get_size(); i++)
  {
    curr_contact_node = m_track_contacts(i);

    // Calculate the Global position and velocity of the contact node.
    contact_node_vel = kMath::h_Vec(0, 0, 0);
    contact_node_pos = kMath::h_Point(curr_contact_node.m_pos_x, curr_contact_node.m_pos_y, curr_contact_node.m_pos_z);

    contact_node_vel =
      kMath::h_VRoty(In_Crick.m_LFT.m_Joint_Angle, In_Crick.m_LFT.m_Joint_Vel, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_Roty(In_Crick.m_LFT.m_Joint_Angle);

    contact_node_pos += kMath::h_Vec(MODEL_LFT_Origin_X, MODEL_LFT_Origin_Y, MODEL_LFT_Origin_Z);

    contact_node_vel =
      kMath::h_VRotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                        In_Crick.m_BDY.m_Pos_Quat4, In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                        In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                                         In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4);

    contact_node_vel += kMath::h_Vec(In_Crick.m_BDY.m_Vel_X, In_Crick.m_BDY.m_Vel_Y, In_Crick.m_BDY.m_Vel_Z);
    contact_node_pos += kMath::h_Vec(In_Crick.m_BDY.m_Pos_X, In_Crick.m_BDY.m_Pos_Y, In_Crick.m_BDY.m_Pos_Z);

    // Determine maximum velocity.
    if (contact_node_vel.mag() > max_vel) max_vel = contact_node_vel.mag();

    // Test to see if this space is occupied by floor.
    curr_floor_node = m_environment.getFloor(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_LFT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_LFT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_LFT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_LFT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_LFT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_LFT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_LFT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_LFT_COG_Z) * contact_force_local(1);
      In_Crick.m_LFT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_LFT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_LFT_COG_Z) * contact_force_local(0);
      In_Crick.m_LFT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_LFT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_LFT_COG_Y) * contact_force_local(0);
    }

    // Test to see if this space is occupied by ceiling.
    curr_floor_node = m_environment.getCeiling(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_LFT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_LFT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_LFT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_LFT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_LFT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_LFT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_LFT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_LFT_COG_Z) * contact_force_local(1);
      In_Crick.m_LFT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_LFT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_LFT_COG_Z) * contact_force_local(0);
      In_Crick.m_LFT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_LFT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_LFT_COG_Y) * contact_force_local(0);
    }
  }
}

void kSim::Sim_Struct::Calc_ExtFM_RRT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel)
{
  // Pre-allocate memory for calculations used in the system, this saves
  // re-allocation time.
  kSim::Contact_List::Contact_Node curr_contact_node;
  kMath::hVector contact_node_pos;
  kMath::hVector contact_node_vel;
  kMath::hVector contact_node_normal;
  kSim::Sim_Env_Struct::Sim_Env_Box curr_floor_node;
  kMath::hVector contact_force_global;
  kMath::hVector contact_force_local;

  In_Crick.m_RRT.m_ExtF_X = 0;
  In_Crick.m_RRT.m_ExtF_Y = 0;
  In_Crick.m_RRT.m_ExtF_Z = 0;
  In_Crick.m_RRT.m_ExtM_X = 0;
  In_Crick.m_RRT.m_ExtM_Y = 0;
  In_Crick.m_RRT.m_ExtM_Z = 0;

  // Cycle through each of the contact nodes in the list.
  for (int i = 0; i < m_track_contacts.get_size(); i++)
  {
    curr_contact_node = m_track_contacts(i);
    curr_contact_node.m_pos_y *= -1.0;   // Only for tracks on the right hand side.
    curr_contact_node.m_norm_y *= -1.0;  // Only for tracks on the right hand side.

    // Calculate the Global position and velocity of the contact node.
    contact_node_vel = kMath::h_Vec(0, 0, 0);
    contact_node_pos = kMath::h_Point(curr_contact_node.m_pos_x, curr_contact_node.m_pos_y, curr_contact_node.m_pos_z);

    contact_node_vel =
      kMath::h_VRoty(In_Crick.m_RRT.m_Joint_Angle, In_Crick.m_RRT.m_Joint_Vel, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_Roty(In_Crick.m_RRT.m_Joint_Angle);

    contact_node_pos += kMath::h_Vec(MODEL_RRT_Origin_X, MODEL_RRT_Origin_Y, MODEL_RRT_Origin_Z);

    contact_node_vel =
      kMath::h_VRotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                        In_Crick.m_BDY.m_Pos_Quat4, In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                        In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                                         In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4);

    contact_node_vel += kMath::h_Vec(In_Crick.m_BDY.m_Vel_X, In_Crick.m_BDY.m_Vel_Y, In_Crick.m_BDY.m_Vel_Z);
    contact_node_pos += kMath::h_Vec(In_Crick.m_BDY.m_Pos_X, In_Crick.m_BDY.m_Pos_Y, In_Crick.m_BDY.m_Pos_Z);

    // Determine maximum velocity.
    if (contact_node_vel.mag() > max_vel) max_vel = contact_node_vel.mag();

    // Test to see if this space is occupied by floor.
    curr_floor_node = m_environment.getFloor(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_RRT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_RRT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_RRT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_RRT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_RRT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_RRT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_RRT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_RRT_COG_Z) * contact_force_local(1);
      In_Crick.m_RRT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_RRT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_RRT_COG_Z) * contact_force_local(0);
      In_Crick.m_RRT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_RRT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_RRT_COG_Y) * contact_force_local(0);
    }

    // Test to see if this space is occupied by ceiling.
    curr_floor_node = m_environment.getCeiling(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_RRT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_RRT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_RRT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_RRT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_RRT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_RRT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_RRT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_RRT_COG_Z) * contact_force_local(1);
      In_Crick.m_RRT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_RRT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_RRT_COG_Z) * contact_force_local(0);
      In_Crick.m_RRT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_RRT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_RRT_COG_Y) * contact_force_local(0);
    }
  }
}

void kSim::Sim_Struct::Calc_ExtFM_LRT(kSim::Sim_Crick_Struct& In_Crick, double& max_vel)
{
  // Pre-allocate memory for calculations used in the system, this saves
  // re-allocation time.
  kSim::Contact_List::Contact_Node curr_contact_node;
  kMath::hVector contact_node_pos;
  kMath::hVector contact_node_vel;
  kMath::hVector contact_node_normal;
  kSim::Sim_Env_Struct::Sim_Env_Box curr_floor_node;
  kMath::hVector contact_force_global;
  kMath::hVector contact_force_local;

  In_Crick.m_LRT.m_ExtF_X = 0;
  In_Crick.m_LRT.m_ExtF_Y = 0;
  In_Crick.m_LRT.m_ExtF_Z = 0;
  In_Crick.m_LRT.m_ExtM_X = 0;
  In_Crick.m_LRT.m_ExtM_Y = 0;
  In_Crick.m_LRT.m_ExtM_Z = 0;

  // Cycle through each of the contact nodes in the list.
  for (int i = 0; i < m_track_contacts.get_size(); i++)
  {
    curr_contact_node = m_track_contacts(i);

    // Calculate the Global position and velocity of the contact node.
    contact_node_vel = kMath::h_Vec(0, 0, 0);
    contact_node_pos = kMath::h_Point(curr_contact_node.m_pos_x, curr_contact_node.m_pos_y, curr_contact_node.m_pos_z);

    contact_node_vel =
      kMath::h_VRoty(In_Crick.m_LRT.m_Joint_Angle, In_Crick.m_LRT.m_Joint_Vel, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_Roty(In_Crick.m_LRT.m_Joint_Angle);

    contact_node_pos += kMath::h_Vec(MODEL_LRT_Origin_X, MODEL_LRT_Origin_Y, MODEL_LRT_Origin_Z);

    contact_node_vel =
      kMath::h_VRotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                        In_Crick.m_BDY.m_Pos_Quat4, In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                        In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4, contact_node_pos, contact_node_vel);
    contact_node_pos *= kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2,
                                         In_Crick.m_BDY.m_Pos_Quat3, In_Crick.m_BDY.m_Pos_Quat4);

    contact_node_vel += kMath::h_Vec(In_Crick.m_BDY.m_Vel_X, In_Crick.m_BDY.m_Vel_Y, In_Crick.m_BDY.m_Vel_Z);
    contact_node_pos += kMath::h_Vec(In_Crick.m_BDY.m_Pos_X, In_Crick.m_BDY.m_Pos_Y, In_Crick.m_BDY.m_Pos_Z);

    // Determine maximum velocity.
    if (contact_node_vel.mag() > max_vel) max_vel = contact_node_vel.mag();

    // Test to see if this space is occupied by floor.
    curr_floor_node = m_environment.getFloor(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_LRT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_LRT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_LRT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_LRT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_LRT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_LRT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_LRT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_LRT_COG_Z) * contact_force_local(1);
      In_Crick.m_LRT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_LRT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_LRT_COG_Z) * contact_force_local(0);
      In_Crick.m_LRT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_LRT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_LRT_COG_Y) * contact_force_local(0);
    }

    // Test to see if this space is occupied by ceiling.
    curr_floor_node = m_environment.getCeiling(contact_node_pos(0), contact_node_pos(1));
    if (contact_node_pos(2) > curr_floor_node.m_low_z && contact_node_pos(2) < curr_floor_node.m_high_z)
    {
      // Convert the contact node normal to global space.
      contact_node_normal =
        kMath::h_RotQuat(In_Crick.m_BDY.m_Pos_Quat1, In_Crick.m_BDY.m_Pos_Quat2, In_Crick.m_BDY.m_Pos_Quat3,
                         In_Crick.m_BDY.m_Pos_Quat4)
        * kMath::h_Roty(In_Crick.m_LRT.m_Joint_Angle)
        * kMath::h_Vec(curr_contact_node.m_norm_x, curr_contact_node.m_norm_y, curr_contact_node.m_norm_z);

      // Determine contact force with respect to global reference frame.
      contact_force_global = this->Calc_Force(curr_floor_node, contact_node_pos, contact_node_vel, contact_node_normal,
                                              curr_contact_node.m_surf_area);

      // Convert the contact force to local frame of reference.
      contact_force_local = kMath::h_Roty(-In_Crick.m_LRT.m_Joint_Angle)
                            * kMath::h_RotQuat(-In_Crick.m_BDY.m_Pos_Quat1, -In_Crick.m_BDY.m_Pos_Quat2,
                                               -In_Crick.m_BDY.m_Pos_Quat3, -In_Crick.m_BDY.m_Pos_Quat4)
                            * contact_force_global;

      // Add force to ExtF/ExtM
      In_Crick.m_LRT.m_ExtF_X += contact_force_local(0);
      In_Crick.m_LRT.m_ExtF_Y += contact_force_local(1);
      In_Crick.m_LRT.m_ExtF_Z += contact_force_local(2);
      In_Crick.m_LRT.m_ExtM_X += (curr_contact_node.m_pos_y - MODEL_LRT_COG_Y) * contact_force_local(2)
                                 - 1 * (curr_contact_node.m_pos_z - MODEL_LRT_COG_Z) * contact_force_local(1);
      In_Crick.m_LRT.m_ExtM_Y += -1 * (curr_contact_node.m_pos_x - MODEL_LRT_COG_X) * contact_force_local(2)
                                 + (curr_contact_node.m_pos_z - MODEL_LRT_COG_Z) * contact_force_local(0);
      In_Crick.m_LRT.m_ExtM_Z += (curr_contact_node.m_pos_x - MODEL_LRT_COG_X) * contact_force_local(1)
                                 - 1 * (curr_contact_node.m_pos_y - MODEL_LRT_COG_Y) * contact_force_local(0);
    }
  }
}
