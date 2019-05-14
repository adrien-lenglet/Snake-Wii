/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_matrix
*/

#include "headers.h"

static void update_culling(shader_t shader)
{
    (void)shader;
    /*if (_demo->buf.cull_state != _demo->shader[shader].do_cull) {
        if (_demo->buf.cull_state)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        _demo->buf.cull_state = _demo->shader[shader].do_cull;
    }*/
}

void shader_set(shader_t shader, dmat4 mvp, dmat4 world, dmat4 rot)
{
    (void)mvp;
    (void)world;
    (void)rot;
    /*mat4 mvp_actual;
    mat4 world_actual;
    mat4 rot_actual;

    dmat4_mat4(mvp, mvp_actual);
    dmat4_mat4(world, world_actual);
    dmat4_mat4(rot, rot_actual);
    glUseProgram(_demo->shader[shader].program);
    glUniformMatrix4fv(_demo->shader[shader].uniform[0],
    1, GL_FALSE, (void*)mvp_actual);
    glUniformMatrix4fv(_demo->shader[shader].uniform[1],
    1, GL_FALSE, (void*)world_actual);
    glUniformMatrix4fv(_demo->shader[shader].uniform[2],
    1, GL_FALSE, (void*)rot_actual);*/
    update_culling(shader);
}

void refresh_vp(demo_t *demo)
{
    Mtx44 proj;
    dvec3 u = ivec3_dvec3(_demo->cam.u);
    dvec3 u_prev = ivec3_dvec3(_demo->cam.u_prev);
    dvec3 f = ivec3_dvec3(_demo->cam.f);
    dvec3 f_prev = ivec3_dvec3(_demo->cam.f_prev);
    size_t rot_max = 12;

    _demo->cam.rot_anim++;
    if (_demo->cam.rot_anim > rot_max)
        _demo->cam.rot_anim = rot_max;
    double ratio = (double)_demo->cam.rot_anim / (double)rot_max;
    u = dvec3_interpolate(u_prev, u, ratio);
    f = dvec3_interpolate(f_prev, f, ratio);
    dmat4_lookdir(ivec3_dvec3(_demo->cam.pos), f, u, _demo->cam.mvp.view);
    demo->cam.mvp.view[0][2] *= -1;
    demo->cam.mvp.view[1][2] *= -1;
    demo->cam.mvp.view[2][2] *= -1;
    demo->cam.mvp.view[3][2] *= -1;
    guPerspective(proj, 90.0f, (f32)_demo->win.w /_demo->win.h , 0.1f, 1000.0f);
    GX_LoadProjectionMtx(proj, GX_PERSPECTIVE);
}
