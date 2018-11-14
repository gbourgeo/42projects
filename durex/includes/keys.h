/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2018/10/31 18:37:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/* Logic over key_table and all the possibilities over a single key :

Example Key 'a', his buffer looks like this,
	[0]		
	[1]		shift
	[2]		altgr
	[3]		shift	altgr
	[4]		control
	[5]		shift	control
	[6]		altgr	control
	[7]		shift	altgr	control
	[8]		alt
	[9]		shift	alt
	[10]	altgr	alt
	[11]	shift	altgr	alt
	[12]	control	alt
	[13]	shift	control	alt
	[14]	altgr	control	alt
	[15]	shift	altgr	control	alt
	[16]	shiftl
	[17]	shift	shiftl
	[18]	altgr	shiftl
	[19]	shift	altgr	shiftl
	[20]	control	shiftl
	[21]	shift	control	shiftl
	[22]	altgr	control	shiftl
	[23]	shift	altgr	control	shiftl
	[24]	alt	shiftl
	[25]	shift	alt	shiftl
	[26]	altgr	alt	shiftl
	[27]	shift	altgr	alt	shiftl
	[28]	control	alt	shiftl
	[29]	shift	control	alt	shiftl
	[30]	altgr	control	alt	shiftl
	[31]	shift	altgr	control	alt	shiftl
	[32]	shiftr
	[33]	shift	shiftr
	[34]	altgr	shiftr
	[35]	shift	altgr	shiftr
	[36]	control	shiftr
	[37]	shift	control	shiftr
	[38]	altgr	control	shiftr
	[39]	shift	altgr	control	shiftr
	[40]	alt	shiftr
	[41]	shift	alt	shiftr
	[42]	altgr	alt	shiftr
	[43]	shift	altgr	alt	shiftr
	[44]	control	alt	shiftr
	[45]	shift	control	alt	shiftr
	[46]	altgr	control	alt	shiftr
	[47]	shift	altgr	control	alt	shiftr
	[48]	shiftl	shiftr
	[49]	shift	shiftl	shiftr
	[50]	altgr	shiftl	shiftr
	[51]	shift	altgr	shiftl	shiftr
	[52]	control	shiftl	shiftr
	[53]	shift	control	shiftl	shiftr
	[54]	altgr	control	shiftl	shiftr
	[55]	shift	altgr	control	shiftl	shiftr
	[56]	alt	shiftl	shiftr
	[57]	shift	alt	shiftl	shiftr
	[58]	altgr	alt	shiftl	shiftr
	[59]	shift	altgr	alt	shiftl	shiftr
	[60]	control	alt	shiftl	shiftr
	[61]	shift	control	alt	shiftl	shiftr
	[62]	altgr	control	alt	shiftl	shiftr
	[63]	shift	altgr	control	alt	shiftl	shiftr
	[64]	ctrll
	[65]	shift	ctrll
	[66]	altgr	ctrll
	[67]	shift	altgr	ctrll
	[68]	control	ctrll
	[69]	shift	control	ctrll
	[70]	altgr	control	ctrll
	[71]	shift	altgr	control	ctrll
	[72]	alt	ctrll
	[73]	shift	alt	ctrll
	[74]	altgr	alt	ctrll
	[75]	shift	altgr	alt	ctrll
	[76]	control	alt	ctrll
	[77]	shift	control	alt	ctrll
	[78]	altgr	control	alt	ctrll
	[79]	shift	altgr	control	alt	ctrll
	[80]	shiftl	ctrll
	[81]	shift	shiftl	ctrll
	[82]	altgr	shiftl	ctrll
	[83]	shift	altgr	shiftl	ctrll
	[84]	control	shiftl	ctrll
	[85]	shift	control	shiftl	ctrll
	[86]	altgr	control	shiftl	ctrll
	[87]	shift	altgr	control	shiftl	ctrll
	[88]	alt	shiftl	ctrll
	[89]	shift	alt	shiftl	ctrll
	[90]	altgr	alt	shiftl	ctrll
	[91]	shift	altgr	alt	shiftl	ctrll
	[92]	control	alt	shiftl	ctrll
	[93]	shift	control	alt	shiftl	ctrll
	[94]	altgr	control	alt	shiftl	ctrll
	[95]	shift	altgr	control	alt	shiftl	ctrll
	[96]	shiftr	ctrll
	[97]	shift	shiftr	ctrll
	[98]	altgr	shiftr	ctrll
	[99]	shift	altgr	shiftr	ctrll
	[100]	control	shiftr	ctrll
	[101]	shift	control	shiftr	ctrll
	[102]	altgr	control	shiftr	ctrll
	[103]	shift	altgr	control	shiftr	ctrll
	[104]	alt	shiftr	ctrll
	[105]	shift	alt	shiftr	ctrll
	[106]	altgr	alt	shiftr	ctrll
	[107]	shift	altgr	alt	shiftr	ctrll
	[108]	control	alt	shiftr	ctrll
	[109]	shift	control	alt	shiftr	ctrll
	[110]	altgr	control	alt	shiftr	ctrll
	[111]	shift	altgr	control	alt	shiftr	ctrll
	[112]	shiftl	shiftr	ctrll
	[113]	shift	shiftl	shiftr	ctrll
	[114]	altgr	shiftl	shiftr	ctrll
	[115]	shift	altgr	shiftl	shiftr	ctrll
	[116]	control	shiftl	shiftr	ctrll
	[117]	shift	control	shiftl	shiftr	ctrll
	[118]	altgr	control	shiftl	shiftr	ctrll
	[119]	shift	altgr	control	shiftl	shiftr	ctrll
	[120]	alt	shiftl	shiftr	ctrll
	[121]	shift	alt	shiftl	shiftr	ctrll
	[122]	altgr	alt	shiftl	shiftr	ctrll
	[123]	shift	altgr	alt	shiftl	shiftr	ctrll
	[124]	control	alt	shiftl	shiftr	ctrll
	[125]	shift	control	alt	shiftl	shiftr	ctrll
	[126]	altgr	control	alt	shiftl	shiftr	ctrll
	[127]	shift	altgr	control	alt	shiftl	shiftr	ctrll
	[128]	ctrlr
	[129]	shift	ctrlr
	[130]	altgr	ctrlr
	[131]	shift	altgr	ctrlr
	[132]	control	ctrlr
	[133]	shift	control	ctrlr
	[134]	altgr	control	ctrlr
	[135]	shift	altgr	control	ctrlr
	[136]	alt	ctrlr
	[137]	shift	alt	ctrlr
	[138]	altgr	alt	ctrlr
	[139]	shift	altgr	alt	ctrlr
	[140]	control	alt	ctrlr
	[141]	shift	control	alt	ctrlr
	[142]	altgr	control	alt	ctrlr
	[143]	shift	altgr	control	alt	ctrlr
	[144]	shiftl	ctrlr
	[145]	shift	shiftl	ctrlr
	[146]	altgr	shiftl	ctrlr
	[147]	shift	altgr	shiftl	ctrlr
	[148]	control	shiftl	ctrlr
	[149]	shift	control	shiftl	ctrlr
	[150]	altgr	control	shiftl	ctrlr
	[151]	shift	altgr	control	shiftl	ctrlr
	[152]	alt	shiftl	ctrlr
	[153]	shift	alt	shiftl	ctrlr
	[154]	altgr	alt	shiftl	ctrlr
	[155]	shift	altgr	alt	shiftl	ctrlr
	[156]	control	alt	shiftl	ctrlr
	[157]	shift	control	alt	shiftl	ctrlr
	[158]	altgr	control	alt	shiftl	ctrlr
	[159]	shift	altgr	control	alt	shiftl	ctrlr
	[160]	shiftr	ctrlr
	[161]	shift	shiftr	ctrlr
	[162]	altgr	shiftr	ctrlr
	[163]	shift	altgr	shiftr	ctrlr
	[164]	control	shiftr	ctrlr
	[165]	shift	control	shiftr	ctrlr
	[166]	altgr	control	shiftr	ctrlr
	[167]	shift	altgr	control	shiftr	ctrlr
	[168]	alt	shiftr	ctrlr
	[169]	shift	alt	shiftr	ctrlr
	[170]	altgr	alt	shiftr	ctrlr
	[171]	shift	altgr	alt	shiftr	ctrlr
	[172]	control	alt	shiftr	ctrlr
	[173]	shift	control	alt	shiftr	ctrlr
	[174]	altgr	control	alt	shiftr	ctrlr
	[175]	shift	altgr	control	alt	shiftr	ctrlr
	[176]	shiftl	shiftr	ctrlr
	[177]	shift	shiftl	shiftr	ctrlr
	[178]	altgr	shiftl	shiftr	ctrlr
	[179]	shift	altgr	shiftl	shiftr	ctrlr
	[180]	control	shiftl	shiftr	ctrlr
	[181]	shift	control	shiftl	shiftr	ctrlr
	[182]	altgr	control	shiftl	shiftr	ctrlr
	[183]	shift	altgr	control	shiftl	shiftr	ctrlr
	[184]	alt	shiftl	shiftr	ctrlr
	[185]	shift	alt	shiftl	shiftr	ctrlr
	[186]	altgr	alt	shiftl	shiftr	ctrlr
	[187]	shift	altgr	alt	shiftl	shiftr	ctrlr
	[188]	control	alt	shiftl	shiftr	ctrlr
	[189]	shift	control	alt	shiftl	shiftr	ctrlr
	[190]	altgr	control	alt	shiftl	shiftr	ctrlr
	[191]	shift	altgr	control	alt	shiftl	shiftr	ctrlr
	[192]	ctrll	ctrlr
	[193]	shift	ctrll	ctrlr
	[194]	altgr	ctrll	ctrlr
	[195]	shift	altgr	ctrll	ctrlr
	[196]	control	ctrll	ctrlr
	[197]	shift	control	ctrll	ctrlr
	[198]	altgr	control	ctrll	ctrlr
	[199]	shift	altgr	control	ctrll	ctrlr
	[200]	alt	ctrll	ctrlr
	[201]	shift	alt	ctrll	ctrlr
	[202]	altgr	alt	ctrll	ctrlr
	[203]	shift	altgr	alt	ctrll	ctrlr
	[204]	control	alt	ctrll	ctrlr
	[205]	shift	control	alt	ctrll	ctrlr
	[206]	altgr	control	alt	ctrll	ctrlr
	[207]	shift	altgr	control	alt	ctrll	ctrlr
	[208]	shiftl	ctrll	ctrlr
	[209]	shift	shiftl	ctrll	ctrlr
	[210]	altgr	shiftl	ctrll	ctrlr
	[211]	shift	altgr	shiftl	ctrll	ctrlr
	[212]	control	shiftl	ctrll	ctrlr
	[213]	shift	control	shiftl	ctrll	ctrlr
	[214]	altgr	control	shiftl	ctrll	ctrlr
	[215]	shift	altgr	control	shiftl	ctrll	ctrlr
	[216]	alt	shiftl	ctrll	ctrlr
	[217]	shift	alt	shiftl	ctrll	ctrlr
	[218]	altgr	alt	shiftl	ctrll	ctrlr
	[219]	shift	altgr	alt	shiftl	ctrll	ctrlr
	[220]	control	alt	shiftl	ctrll	ctrlr
	[221]	shift	control	alt	shiftl	ctrll	ctrlr
	[222]	altgr	control	alt	shiftl	ctrll	ctrlr
	[223]	shift	altgr	control	alt	shiftl	ctrll	ctrlr
	[224]	shiftr	ctrll	ctrlr
	[225]	shift	shiftr	ctrll	ctrlr
	[226]	altgr	shiftr	ctrll	ctrlr
	[227]	shift	altgr	shiftr	ctrll	ctrlr
	[228]	control	shiftr	ctrll	ctrlr
	[229]	shift	control	shiftr	ctrll	ctrlr
	[230]	altgr	control	shiftr	ctrll	ctrlr
	[231]	shift	altgr	control	shiftr	ctrll	ctrlr
	[232]	alt	shiftr	ctrll	ctrlr
	[233]	shift	alt	shiftr	ctrll	ctrlr
	[234]	altgr	alt	shiftr	ctrll	ctrlr
	[235]	shift	altgr	alt	shiftr	ctrll	ctrlr
	[236]	control	alt	shiftr	ctrll	ctrlr
	[237]	shift	control	alt	shiftr	ctrll	ctrlr
	[238]	altgr	control	alt	shiftr	ctrll	ctrlr
	[239]	shift	altgr	control	alt	shiftr	ctrll	ctrlr
	[240]	shiftl	shiftr	ctrll	ctrlr
	[241]	shift	shiftl	shiftr	ctrll	ctrlr
	[242]	altgr	shiftl	shiftr	ctrll	ctrlr
	[243]	shift	altgr	shiftl	shiftr	ctrll	ctrlr
	[244]	control	shiftl	shiftr	ctrll	ctrlr
	[245]	shift	control	shiftl	shiftr	ctrll	ctrlr
	[246]	altgr	control	shiftl	shiftr	ctrll	ctrlr
	[247]	shift	altgr	control	shiftl	shiftr	ctrll	ctrlr
	[248]	alt	shiftl	shiftr	ctrll	ctrlr
	[249]	shift	alt	shiftl	shiftr	ctrll	ctrlr
	[250]	altgr	alt	shiftl	shiftr	ctrll	ctrlr
	[251]	shift	altgr	alt	shiftl	shiftr	ctrll	ctrlr
	[252]	control	alt	shiftl	shiftr	ctrll	ctrlr
	[253]	shift	control	alt	shiftl	shiftr	ctrll	ctrlr
	[254]	altgr	control	alt	shiftl	shiftr	ctrll	ctrlr
	[255]	shift	altgr	control	alt	shiftl	shiftr	ctrll	ctrlr
*/

typedef struct 	s_syms
{
	const char	**table;
	int 		size;
}				t_syms;

/* Keysyms whose KTYP is KT_LATIN or KT_LETTER and whose KVAL is 0..127. */
static const char *iso646_syms[] = {
	"<nul>",
	"<Control_a>",
	"<Control_b>",
	"<Control_c>",
	"<Control_d>",
	"<Control_e>",
	"<Control_f>",
	"<Control_g>",
	"<BackSpace>",
	"<Tab>",
	"<Linefeed>",
	"<Control_k>",
	"<Control_l>",
	"<Control_m>",
	"<Control_n>",
	"<Control_o>",
	"<Control_p>",
	"<Control_q>",
	"<Control_r>",
	"<Control_s>",
	"<Control_t>",
	"<Control_u>",
	"<Control_v>",
	"<Control_w>",
	"<Control_x>",
	"<Control_y>",
	"<Control_z>",
	"<Escape>",
	"<Control_backslash>",
	"<Control_bracketright>",
	"<Control_asciicircum>",
	"<Control_underscore>",
	" ",
	"!",
	"\"",
	"#",
	"$",
	"%",
	"&",
	"\'",
	"(",
	")",
	"*",
	"+",
	",",
	"-",
	".",
	"/",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	":",
	";",
	"<",
	"=",
	">",
	"?",
	"@",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"[",
	"\\",
	"]",
	"^",
	"_",
	"`",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"{",
	"|",
	"}",
	"~",
	"<Delete>",
	/* set_charset() fills in charset dependent strings here. */
	/* start with the latin1 defaults */
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"<nobreakspace>",
	"¡",
	"¢",
	"£",
	"¤",
	"¥",
	"¦",
	"§",
	"¨",
	"©",
	"ª",
	"«",
	"¬",
	"<hyphen>",
	"®",
	"¯",
	"°",
	"±",
	"²",
	"³",
	"´",
	"µ",
	"¶",
	"·",
	"¸",
	"¹",
	"º",
	"»",
	"¼",
	"½",
	"¾",
	"¿",
	"À",
	"Á",
	"Â",
	"Ã",
	"Ä",
	"Å",
	"Æ",
	"Ç",
	"È",
	"É",
	"Ê",
	"Ë",
	"Ì",
	"Í",
	"Î",
	"Ï",
	"Ð",
	"Ñ",
	"Ò",
	"Ó",
	"Ô",
	"Õ",
	"Ö",
	"×",
	"Ø",
	"Ù",
	"Ú",
	"Û",
	"Ü",
	"Ý",
	"Þ",
	"ß",
	"à",
	"á",
	"â",
	"ã",
	"ä",
	"å",
	"æ",
	"ç",
	"è",
	"é",
	"ê",
	"ë",
	"ì",
	"í",
	"î",
	"ï",
	"ð",
	"ñ",
	"ò",
	"ó",
	"ô",
	"õ",
	"ö",
	"÷",
	"ø",
	"ù",
	"ú",
	"û",
	"ü",
	"ý",
	"þ",
	"ÿ",
};

/* Keysyms whose KTYP is KT_FN. */
static const char *fn_syms[] = {
	"<F1>", 	"<F2>",		"<F3>",		"<F4>",		"<F5>",
	"<F6>",		"<F7>",		"<F8>",		"<F9>",		"<F10>",
	"<F11>",	"<F12>",	"<F13>",	"<F14>",	"<F15>",
	"<F16>",	"<F17>",	"<F18>",	"<F19>",	"<F20>",
	"<Find>",			/* also called: "Home" */
	"<Insert>",
	"<Remove>",
	"<Select>",		/* also called: "End" */
	"<Prior>",		/* also called: "PageUp" */
	"<Next>",			/* also called: "PageDown" */
	"<Macro>",
	"<Help>",
	"<Do>",
	"<Pause>",
	"<F21>",	"<F22>",	"<F23>",	"<F24>",	"<F25>",
	"<F26>",	"<F27>",	"<F28>",	"<F29>",	"<F30>",
	"<F31>",	"<F32>",	"<F33>",	"<F34>",	"<F35>",
	"<F36>",	"<F37>",	"<F38>",	"<F39>",	"<F40>",
	"<F41>",	"<F42>",	"<F43>",	"<F44>",	"<F45>",
	"<F46>",	"<F47>",	"<F48>",	"<F49>",	"<F50>",
	"<F51>",	"<F52>",	"<F53>",	"<F54>",	"<F55>",
	"<F56>",	"<F57>",	"<F58>",	"<F59>",	"<F60>",
	"<F61>",	"<F62>",	"<F63>",	"<F64>",	"<F65>",
	"<F66>",	"<F67>",	"<F68>",	"<F69>",	"<F70>",
	"<F71>",	"<F72>",	"<F73>",	"<F74>",	"<F75>",
	"<F76>",	"<F77>",	"<F78>",	"<F79>",	"<F80>",
	"<F81>",	"<F82>",	"<F83>",	"<F84>",	"<F85>",
	"<F86>",	"<F87>",	"<F88>",	"<F89>",	"<F90>",
	"<F91>",	"<F92>",	"<F93>",	"<F94>",	"<F95>",
	"<F96>",	"<F97>",	"<F98>",	"<F99>",	"<F100>",
	"<F101>",	"<F102>",	"<F103>",	"<F104>",	"<F105>",
	"<F106>",	"<F107>",	"<F108>",	"<F109>",	"<F110>",
	"<F111>",	"<F112>",	"<F113>",	"<F114>",	"<F115>",
	"<F116>",	"<F117>",	"<F118>",	"<F119>",	"<F120>",
	"<F121>",	"<F122>",	"<F123>",	"<F124>",	"<F125>",
	"<F126>",	"<F127>",	"<F128>",	"<F129>",	"<F130>",
	"<F131>",	"<F132>",	"<F133>",	"<F134>",	"<F135>",
	"<F136>",	"<F137>",	"<F138>",	"<F139>",	"<F140>",
	"<F141>",	"<F142>",	"<F143>",	"<F144>",	"<F145>",
	"<F146>",	"<F147>",	"<F148>",	"<F149>",	"<F150>",
	"<F151>",	"<F152>",	"<F153>",	"<F154>",	"<F155>",
	"<F156>",	"<F157>",	"<F158>",	"<F159>",	"<F160>",
	"<F161>",	"<F162>",	"<F163>",	"<F164>",	"<F165>",
	"<F166>",	"<F167>",	"<F168>",	"<F169>",	"<F170>",
	"<F171>",	"<F172>",	"<F173>",	"<F174>",	"<F175>",
	"<F176>",	"<F177>",	"<F178>",	"<F179>",	"<F180>",
	"<F181>",	"<F182>",	"<F183>",	"<F184>",	"<F185>",
	"<F186>",	"<F187>",	"<F188>",	"<F189>",	"<F190>",
	"<F191>",	"<F192>",	"<F193>",	"<F194>",	"<F195>",
	"<F196>",	"<F197>",	"<F198>",	"<F199>",	"<F200>",
	"<F201>",	"<F202>",	"<F203>",	"<F204>",	"<F205>",
	"<F206>",	"<F207>",	"<F208>",	"<F209>",	"<F210>",
	"<F211>",	"<F212>",	"<F213>",	"<F214>",	"<F215>",
	"<F216>",	"<F217>",	"<F218>",	"<F219>",	"<F220>",
	"<F221>",	"<F222>",	"<F223>",	"<F224>",	"<F225>",
	"<F226>",	"<F227>",	"<F228>",	"<F229>",	"<F230>",
	"<F231>",	"<F232>",	"<F233>",	"<F234>",	"<F235>",
	"<F236>",	"<F237>",	"<F238>",	"<F239>",	"<F240>",
	"<F241>",	"<F242>",	"<F243>",	"<F244>",	"<F245>",
	"<F246>"		/* there are 10 keys named Insert etc., total 256 */
};

/* Keysyms whose KTYP is KT_SPEC. */
static const char *spec_syms[] = {
	"<VoidSymbol>",
	"<Return>\n",
	"<Show_Registers>",
	"<Show_Memory>",
	"<Show_State>",
	"<Break>",
	"<Last_Console>",
	"<Caps_Lock>",
	"<Num_Lock>",
	"<Scroll_Lock>",
	"<Scroll_Forward>",
	"<Scroll_Backward>",
	"<Boot>",
	"<Caps_On>",
	"<Compose>",
	"<SAK>",
	"<Decr_Console>",
	"<Incr_Console>",
	"<KeyboardSignal>",
	"<Bare_Num_Lock>"
};

/* Keysyms whose KTYP is KT_PAD. */
static const char *pad_syms[] = {
	"<KP_0>",
	"<KP_1>",
	"<KP_2>",
	"<KP_3>",
	"<KP_4>",
	"<KP_5>",
	"<KP_6>",
	"<KP_7>",
	"<KP_8>",
	"<KP_9>",
	"<KP_Add>",
	"<KP_Subtract>",
	"<KP_Multiply>",
	"<KP_Divide>",
	"<KP_Enter>",
	"<KP_Comma>",
	"<KP_Period>",
	"<KP_MinPlus>"
};

/* Keysyms whose KTYP is KT_DEAD. */
static const char *dead_syms[] = {
	"`",
	"´",
	"^",
	"˜",
	"¨",
	"¸"
};

/* Keysyms whose KTYP is KT_CONS. */
static const char *cons_syms[] = {
	"<Console_1>",
	"<Console_2>",
	"<Console_3>",
	"<Console_4>",
	"<Console_5>",
	"<Console_6>",
	"<Console_7>",
	"<Console_8>",
	"<Console_9>",
	"<Console_10>",
	"<Console_11>",
	"<Console_12>",
	"<Console_13>",
	"<Console_14>",
	"<Console_15>",
	"<Console_16>",
	"<Console_17>",
	"<Console_18>",
	"<Console_19>",
	"<Console_20>",
	"<Console_21>",
	"<Console_22>",
	"<Console_23>",
	"<Console_24>",
	"<Console_25>",
	"<Console_26>",
	"<Console_27>",
	"<Console_28>",
	"<Console_29>",
	"<Console_30>",
	"<Console_31>",
	"<Console_32>",
	"<Console_33>",
	"<Console_34>",
	"<Console_35>",
	"<Console_36>",
	"<Console_37>",
	"<Console_38>",
	"<Console_39>",
	"<Console_40>",
	"<Console_41>",
	"<Console_42>",
	"<Console_43>",
	"<Console_44>",
	"<Console_45>",
	"<Console_46>",
	"<Console_47>",
	"<Console_48>",
	"<Console_49>",
	"<Console_50>",
	"<Console_51>",
	"<Console_52>",
	"<Console_53>",
	"<Console_54>",
	"<Console_55>",
	"<Console_56>",
	"<Console_57>",
	"<Console_58>",
	"<Console_59>",
	"<Console_60>",
	"<Console_61>",
	"<Console_62>",
	"<Console_63>"
};

/* Keysyms whose KTYP is KT_CUR. */
static const char *cur_syms[] = {
	"<Down>",
	"<Left>",
	"<Right>",
	"<Up>"
};

/* Keysyms whose KTYP is KT_SHIFT. */
static const char *shift_syms[] = {
	"Shift",
	"AltGr",
	"Control",
	"Alt",
	"ShiftL",
	"ShiftR",
	"CtrlL",
	"CtrlR",
	"CapsShift"
};

/* Keysyms whose KTYP is KT_ASCII. */
static const char *ascii_syms[] = {
	"<Ascii_0>",
	"<Ascii_1>",
	"<Ascii_2>",
	"<Ascii_3>",
	"<Ascii_4>",
	"<Ascii_5>",
	"<Ascii_6>",
	"<Ascii_7>",
	"<Ascii_8>",
	"<Ascii_9>",
	"<Hex_0>",
	"<Hex_1>",
	"<Hex_2>",
	"<Hex_3>",
	"<Hex_4>",
	"<Hex_5>",
	"<Hex_6>",
	"<Hex_7>",
	"<Hex_8>",
	"<Hex_9>",
	"<Hex_A>",
	"<Hex_B>",
	"<Hex_C>",
	"<Hex_D>",
	"<Hex_E>",
	"<Hex_F>"
};

/* Keysyms whose KTYP is KT_LOCK. */
static const char *lock_syms[] = {
	"Shift_Lock",
	"AltGr_Lock",
	"Control_Lock",
	"Alt_Lock",
	"ShiftL_Lock",
	"ShiftR_Lock",
	"CtrlL_Lock",
	"CtrlR_Lock"
};

/* Keysyms whose KTYP is KT_SLOCK. */
static const char *sticky_syms[] = {
	"<SShift>",
	"<SAltGr>",
	"<SControl>",
	"<SAlt>",
	"<SShiftL>",
	"<SShiftR>",
	"<SCtrlL>",
	"<SCtrlR>"
};

# define E(x) { x, sizeof(x) / sizeof(*x) }

t_syms			syms[] = {
	E(iso646_syms),	/* KT_LATIN */
	E(fn_syms),		/* KT_FN */
	E(spec_syms),	/* KT_SPEC */
	E(pad_syms),	/* KT_PAD */
	E(dead_syms),	/* KT_DEAD */
	E(cons_syms),	/* KT_CONS */
	E(cur_syms),	/* KT_CUR */
	E(shift_syms),	/* KT_SHIFT */
	{ 0, 0 },		/* KT_META */
	E(ascii_syms),	/* KT_ASCII */
	E(lock_syms),	/* KT_LOCK */
	{ 0, 0 },		/* KT_LETTER */
	E(sticky_syms)	/* KT_SLOCK */
};

const int 		syms_size = sizeof(syms) / sizeof(*syms);

#endif
