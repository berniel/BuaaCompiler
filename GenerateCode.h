#ifndef GENERATECODE_H_INCLUDED
#define GENERATECODE_H_INCLUDED
extern int start;
extern int page_size;
void generate_code();
void generate_glc(int index);
void generate_glv(int index);
void generate_fdcl(int index);
void generate_neg(int index);
void generate_add(int index);
void generate_asn(int index);
void generate_sub(int index);
void generate_mul(int index);
void generate_div(int index);
void generate_bg(int index);
void generate_ls(int index);
void generate_nls(int index);
void generate_nbg(int index);
void generate_equ(int index);
void generate_neq(int index);
void generate_mdcl(int index);
void generate_end(int index);
void generate_rrt(int index);
void generate_vrt(int index);
void generate_lab(int index);
void generate_goto(int index);
void generate_ngoto(int index);
void generate_tgoto(int index);
void generate_call(int index);
void generate_push(int index);
void generate_mff(int index);
void generate_lfa(int index);
void generate_sta(int index);
void generate_rd(int index);
void generate_wrs(int index);
void generate_wri(int index);
void generate_wrc(int index);
void generate_load_ele(TableEle *te, char rsl[], char t[]);
void generate_save_ele(TableEle *te, char rsl[], char t[]);

#endif // GENERATECODE_H_INCLUDED
