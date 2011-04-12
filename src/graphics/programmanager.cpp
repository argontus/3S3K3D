/**
 * @file graphics/programmanager.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/programmanager.h>

#include <fstream>

#include <graphics/fragmentshader.h>
#include <graphics/runtimeassert.h>
#include <graphics/vertexshader.h>

namespace {

// TODO: decide how errors should be reported
/**
 * Helper function for reading text file contents.
 *
 * @param path A relative or absolute path for the file to open. The file is
 * interpreted as ASCII encoded text file.
 *
 * @return Contents of the specified file.
 */
const std::string readSourceText(const std::string& path)
{
    std::ifstream inputStream;
    inputStream.open(path.c_str(), std::ios::in);

    if (inputStream.is_open() == false)
    {
        // TODO: quick & dirty, decide how errors should be reported
        GRAPHICS_RUNTIME_ASSERT(false);

        return std::string();
    }

    std::string text;
    char c;

    while (inputStream.get(c))
    {
        text += c;
    }

    return text;
}

}

ProgramManager::~ProgramManager()
{
    // ...
}

ProgramManager::ProgramManager()
:   vsManager_(),
    fsManager_(),
    programManager_()
{
    // ...
}

Program* ProgramManager::load(
    const std::string& vsPath,
    const std::string& fsPath)
{
    const std::string programId = vsPath + fsPath;

    Program* program = programManager_.getResource(programId);

    if (program != 0)
    {
        // already compiled and linked, return existing program
        return program;
    }

    VertexShader* vs = 0;

    if (vsPath.empty() == false)
    {
        vs = vsManager_.getResource(vsPath);

        if (vs == 0)
        {
            vs = new VertexShader();
            vs->setSourceText(readSourceText(vsPath));

            if (vs->compile() == false)
            {
                GRAPHICS_RUNTIME_ASSERT(false);
                //const std::string info = vs->infoLog();
                //if (info.size() == 0) return 0;
            }

            vsManager_.loadResource(vsPath, vs);
        }
    }

    FragmentShader* fs = 0;

    if (fsPath.empty() == false)
    {
        fs = fsManager_.getResource(fsPath);

        if (fs == 0)
        {
            fs = new FragmentShader();
            fs->setSourceText(readSourceText(fsPath));

            if (fs->compile() == false)
            {
                GRAPHICS_RUNTIME_ASSERT(false);
                //const std::string info = fs->infoLog();
            }

            fsManager_.loadResource(fsPath, fs);
        }
    }

    program = new Program();
    program->setVertexShader(vs);
    program->setFragmentShader(fs);

    if (program->link() == false)
    {
        GRAPHICS_RUNTIME_ASSERT(false);
        //const std::string info = program->infoLog();
    }

    programManager_.loadResource(programId, program);

    return program;
}
