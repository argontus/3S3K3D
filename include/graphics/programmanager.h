/**
 * @file graphics/programmanager.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PROGRAMMANAGER_H_INCLUDED
#define GRAPHICS_PROGRAMMANAGER_H_INCLUDED

#include <graphics/resourcemanager.h>
#include <graphics/program.h>

class ProgramManager
{
public:
    ~ProgramManager();

    ProgramManager();

    Program* load(const std::string& vsPath, const std::string& fsPath);

private:
    ResourceManager<VertexShader> vsManager_;
    ResourceManager<FragmentShader> fsManager_;
    ResourceManager<Program> programManager_;

    // prevent copying
    ProgramManager(const ProgramManager&);
    ProgramManager& operator =(const ProgramManager&);
};

#endif // #ifndef GRAPHICS_PROGRAMMANAGER_H_INCLUDED
