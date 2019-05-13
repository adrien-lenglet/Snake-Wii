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

    entity3_update_trans_inv(demo->world.camera);
    dmat4_copy(demo->world.camera->trans.world_inv, demo->cam.mvp.view);
    guPerspective(proj, 90.0f, (f32)_demo->win.w /_demo->win.h , 0.1f, 1000.0f);
    GX_LoadProjectionMtx(proj, GX_PERSPECTIVE);
}
