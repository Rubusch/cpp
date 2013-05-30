/*
 * Copyright (c) 2007, IRTrans GmbH
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer. 
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution. 
 *     * Neither the name of IRTrans GmbH nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY IRTrans GmbH ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL IRTrans GmbH BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */




#define REMOTE_CNT	11

#define F_ENABLEGROUP		0
#define F_COMMAND			1
#define F_VOLUMEMACRO		2
#define F_VOLUMEMACROD		3
#define F_CONFIG			4
#define F_REMOTE			5
#define F_SEND				6
#define F_PREKEY			7
#define IRDB_REM			8
#define IRDB_TYPEHEADER		9
#define IRDB_TYPEACTION		10
#define IRDB_TYPEACTION_1	11
#define IRDB_TYPEACTION_2	12
#define IRDB_TYPEACTION_3	13
#define IRDB_TYPEACTION_4	14
#define IRDB_TYPEACTION_5	15
#define IRDB_TYPEACTION_6	16
#define IRDB_TYPEACTION_7	17
#define IRDB_TYPEHEADER_32K	18
#define IRDB_TYPEHEADER_64K	19
#define IRDB_TYPEHEADER_96K	20

#define F_TOGGLE			70
#define F_ERROR				99
#define F_MACRO				100

#define F_MAGIC				0x3542

#define COMPARE_LEN			128

#define PC_MASK				3
#define PC_RECV				1
#define PC_TRANS			2
#define PC_OFF				3

#define TRANSLATE_LAN_INPUT		16
#define TRANSLATE_SBUS_INPUT	32

#define TRANSM_MASK			240

#define TRANSM_INTERN		1
#define TRANSM_EXTERN		2
#define TRANSM_ALL			3
#define TRANSM_EXT1			4
#define TRANSM_EXT2			5
#define TRANSM_EXT3			6
#define TRANSM_EXT4			7
#define TRANSM_EXT5			8
#define TRANSM_EXT6			9
#define TRANSM_EXT7			10


#define SBUS_MASK			12
#define SBUS_RECV			4
#define SBUS_TRANS			8
#define SBUS_OFF			12


#define ACC_WAIT			0xf0
#define ACC_REPEAT			0xf

#ifndef AVR
#pragma pack(1)
#endif

#define MACRO_TIMEOUT	500


// Remote = 0: Globale Informationen

typedef struct {
	word dir_cnt;								//   0
	word data_pnt;								//   2
	word end_pnt;								//   4
	word magic;									//   6
	word checksum;

	byte trans_setup[REMOTE_CNT];				//   8
	byte rcv_len;								//  19
	word target_mask[REMOTE_CNT];				//  20
	word source_mask[REMOTE_CNT];				//  42
	uint32_t group_flags[REMOTE_CNT];			//  64
} FLASH_CONTENT;								// 108

typedef struct {
	FLASH_CONTENT f_content;					//   0
	word last_flashcommand;						// 108
	word command_repeat;						// 110
	uint32_t last_command_time;					// 112
	uint32_t prekey_timeout;					// 116
	byte pre_key;								// 120
	byte toggle_pos[REMOTE_CNT];				// 121
} FLASH_CONTENT_MEMORY;							// 132


extern byte flash_mode;

#define	FLASH_MODE_TRANSLATOR		1
#define FLASH_MODE_IRDB				2
#define FLASH_MODE_IRDBAUX			4
#define FLASH_MODE_LAN_DB			8
#define FLASH_MODE_LANRELAIS		16
#define FLASH_MODE_IRDB_SENDONLY	32
#define FLASH_MODE_SEND_LINE		64
#define FLASH_MODE_SEND_BINARY		128


/* Struktur IRDB:

Alle Adressen relativ auf Nr. des Eintrags ??

0:	IRDB_TABLE
4:	IRDB_HEADER

hi:	HASH_ENTRY für jedes IR Command -> PNT auf IRDB_IRCOMMAND
hc:	HASH_ENTRY für jedes Command -> PNT auf IRDB_COMMAND
hr: HASH_ENTRY für jede Remote -> PNT auf IRDB_REMOTE
c:	IRDB_COMMAND für jedes Command -> PNT auf IRDB_REMOTE + IRDB_TIMING + IRDB_IRCOMMAND
i:	IRDB_IRCOMMAND für jedes Command -> PNT auf IRDB_COMMAND 
r:	IRDB_REMOTE
t:	IRDB_TIMING
a:	IRDB_ACTION

*/


typedef struct {
	byte mode;
	byte hysteresis;
	short low_value;
	short high_value;
} ADC_MARGIN;

typedef struct {
	word low_remote;
	word high_remote;
	word low_mask;
	word high_mask;
	byte low_ledsel;
	byte high_ledsel;
	byte low_commands[50];
	byte high_commands[50];
} ADC_IRDATA;

typedef struct {
	byte mode;
	byte hysteresis;
	byte low_value;
	byte high_value;
	word low_remote;
	word high_remote;
	word low_mask;
	word high_mask;
	byte low_ledsel;
	byte high_ledsel;
	byte low_commands[50];
	byte high_commands[50];
} ADC_ENTRY;


typedef struct {
	word remote_cnt;					//   0
	word remote_adr;					//   2
	word remote_hash_adr;				//   4

#ifndef NO_RECEIVE
	word command_cnt;					//   6
	word ircommand_adr;					//   8
	word ircommand_hash_adr;			//  10
	byte return_stat_ok[21];			//  12
	byte return_stat_err[21];			//  33
	byte default_action[100];			//  54
	uint32_t target_ip;					// 154
	word target_port;					// 158
	byte rs232_config[4];				// 160
	word action_cnt;					// 164
	word action_adr;					// 166
#endif									// 168

} IRDB_TABLE_SHORT;


typedef struct {
	word remote_cnt;
	word remote_adr;
	word remote_hash_adr;
	word command_cnt;
	word ircommand_adr;
	word ircommand_hash_adr;
	byte return_stat_ok[21];
	byte return_stat_err[21];
	byte default_action[100];
	uint32_t target_ip;	
	word target_port;
	byte rs232_config[4];
	word action_cnt;
	word action_adr;
	ADC_MARGIN adc_margin[4];
	ADC_IRDATA adc_irdata[4];
} IRDB_TABLE;

typedef struct {
	word remote_cnt;
	word remote_adr;
	word remote_hash_adr;
	word command_cnt;
	word ircommand_adr;
	word ircommand_hash_adr;
	byte return_stat_ok[21];
	byte return_stat_err[21];
	byte default_action[100];
	uint32_t target_ip;	
	word target_port;
	byte rs232_config[4];
	word action_cnt;
	word action_adr;
	ADC_ENTRY adc[4];
} IRDB_TABLE_V4;

typedef struct {
	word remote_cnt;
	word remote_adr;
	word remote_hash_adr;
	word command_cnt;
	word ircommand_adr;
	word ircommand_hash_adr;
	byte return_stat_ok[21];
	byte return_stat_err[21];
	byte default_action[100];
	ADC_ENTRY adc[4];
} IRDB_TABLE_V3;

typedef struct {
	word crc;
	word type;
	word len;
	IRDB_TABLE_SHORT table;
} IRDB_HEADER_SHORT;

typedef struct {
	word crc;
	word type;
	word len;
	IRDB_TABLE table;
} IRDB_HEADER;

typedef struct {
	word crc;
	word type;
	word len;
	IRDB_TABLE_V4 table;
} IRDB_HEADER_V4;

typedef struct {
	word crc;
	word type;
	word len;
	IRDB_TABLE_V3 table;
} IRDB_HEADER_V3;

typedef struct {
	word crc;
	word type;
	word len;
} IRDB_HEADER_ONLY;

#ifdef TRANSLATOR_IRDB
typedef struct {
#else
typedef union {
#endif
#ifdef FLASHROM_TRANSLATOR
	FLASH_CONTENT_MEMORY translation_mem;
#else
	byte dummy1;
#endif
#if defined (FLASHROM_IRDB)
	IRDB_TABLE_SHORT irdb_mem;
#else
	byte dummy2;
#endif
} FLASH_COMMON_HEADER_SHORT;

//typedef union {
//	FLASH_CONTENT_MEMORY translation_mem;
//	IRDB_TABLE irdb_mem;
//} FLASH_COMMON_HEADER;

extern FLASH_COMMON_HEADER_SHORT f_common;


typedef struct {
	byte name[80];
	word command_cnt;
	word command_hash;
	word command_adr;
} IRDB_REMOTE;

typedef struct {
	word command_cnt;
	word command_hash;
	word command_adr;
	byte namelen;
	byte name[80];
} IRDB_REMOTE_COMPACT;


typedef struct {
	word command_cnt;
	word command_hash;
	word command_adr;
	byte namelen;
	byte defactlen;
	uint32_t ip;
	word port;
	byte modeflags;
	byte name[130];
} IRDB_REMOTE_EX;


typedef struct {
	byte name[20];
	word timing_adr;
	word remote_adr;
	word ird_adr;
	word action_adr;
} IRDB_COMMAND_1;


typedef struct {
	byte name[20];
	word timing_adr;
	word remote_adr;
	word ird_adr;
	word action_adr;
	byte toggle_seq;
	byte dummy;
} IRDB_COMMAND;

typedef struct {
	word timing_adr;
	word remote_adr;
	word ird_adr;
	word action_adr;
	byte toggle_seq;
	byte namelen;
	byte name[20];
} IRDB_COMMAND_COMPACT;

typedef struct {
	byte ir_length;
	byte transmit_freq;
	byte mode;
	word pause_len[TIME_LEN];
	word pulse_len[TIME_LEN];
	byte time_cnt;
	byte ir_repeat;
	byte repeat_pause;
} IRDB_TIMING;

typedef struct {
	byte ir_length;
	byte transmit_freq;
	byte mode;
	word pause_len[TIME_LEN_18];
	word pulse_len[TIME_LEN_18];
	byte time_cnt;
	byte ir_repeat;
	byte repeat_pause;
} IRDB_TIMING_18;

typedef struct {
	byte ir_length;
	byte transmit_freq;
	byte mode;
	word multi_len[TIME_LEN_SINGLE];
	word single_len;
	byte time_cnt;
	byte ir_repeat;
	byte repeat_pause;
} IRDB_TIMING_SINGLE;

typedef struct {
	byte action_len;
	byte action_type;
	byte relais;
	byte action[1];
} IRDB_ACTION;

// Type Flags

#define ACTION_BINARY		1
#define ACTION_UDP_DEFAULT	2
#define ACTION_UDP_UDP		4
#define ACTION_UDP_AUX		8
#define ACTION_IP			16
#define ACTION_PORT			32
#define ACTION_UDP_AUX2		64

typedef struct {
	byte relais;
	byte action_len[3];
	byte action_type[3];
	byte align;
	byte action[1];
} IRDB_ACTION_EX;


typedef struct {
	byte action_len;
	byte action_type;
	byte action[1];
} IRDB_ACTION_DATA;


typedef struct {
	byte relais;
	byte action_cnt;
	word command_adr;
	word total_length;
	byte data[1];
} IRDB_ACTION_HEADER;


typedef struct {
	word command_adr;
	byte ir_length;
	byte ir_data_ir[1];
} IRDB_IRCOMMAND;


#define IRDB_REMOTE_LEN ((sizeof (IRDB_REMOTE) + 1) / 2)
#define IRDB_REMOTE_LEN_COMPACT (sizeof (IRDB_REMOTE_COMPACT) - 79)
#define IRDB_REMOTE_LEN_EX (sizeof (IRDB_REMOTE_EX) - 129)
#define IRDB_COMMAND_LEN ((sizeof (IRDB_COMMAND) + 1) / 2)
#define IRDB_COMMAND_LEN_COMPACT (sizeof (IRDB_COMMAND_COMPACT) - 19)
#define IRDB_COMMAND_LEN_1 ((sizeof (IRDB_COMMAND_1) + 1) / 2)
#define IRDB_HEADER_LEN ((sizeof (IRDB_HEADER) + 1) / 2)
#define IRDB_HEADER_LEN_V3 ((sizeof (IRDB_HEADER_V3) + 1) / 2)
#define IRDB_HEADER_LEN_V4 ((sizeof (IRDB_HEADER_V4) + 1) / 2)
#define IRDB_TIMING_LEN ((sizeof (IRDB_TIMING) + 1) / 2)
#define IRDB_TIMING_SINGLE_LEN ((sizeof (IRDB_TIMING_SINGLE) + 1) / 2)
#define IRDB_TIMING_18_LEN ((sizeof (IRDB_TIMING_18) + 1) / 2)


#define CONTENT_LEN ((sizeof (FLASH_CONTENT) + 1) / 2)
#define HASH_LEN ((sizeof (HASH_ENTRY) + 1) / 2)


typedef struct {
	byte type;
	byte len;
	byte remote;
	byte group;
	word flash_adr;
	word source_mask;
	byte accelerator_timeout;
	byte accelerator_repeat;
	byte trans_setup;
	byte pre_key;
	byte name_len;
	byte data[1];
} FLASH_ENTRY;

typedef struct {
	byte type;
	byte len;
	byte remote;
	byte group;
	word flash_adr;
	word source_mask;
	byte accelerator_timeout;
	byte accelerator_repeat;
	byte trans_setup;
	byte pre_key;
	byte data[1];
} FLASH_ENTRY_2;

typedef struct {
	byte type;
	byte len;
	byte remote;
	byte group;
	word flash_adr;
	word source_mask;
	byte accelerator_timeout;
	byte accelerator_repeat;
	byte trans_setup;
	byte cdata[1];
} FLASH_ENTRY_ORG;

typedef struct {
	word hashcode;
	word adr;
} HASH_ENTRY;

typedef struct {
	byte rcv_start;
	byte rcv_len;
	word adr;
} HASH_ENTRY_OFFSET;


#ifdef AVR

typedef union {
   uint32_t Whole;
   struct 
   {
      byte Data;
      word Remainder;
      byte Head;
   } Part;
} CRC_BUFFER;

void PutCRC(byte b,CRC_BUFFER *crcb);
void CRCStart (CRC_BUFFER *crcb,byte init);
void CRCSet (CRC_BUFFER *crcb,byte *Data, word Length);
word CRC (CRC_BUFFER *crcb);

#endif

void flash_lan (void);
byte init_irdb (word start_adr);
void flash_init (void);
void flash_ioinit (void);
void read_flash_directory (void);
byte flash_exec (byte adr,byte data[],byte len,byte md);
void load_flashcommand (word adr,IRDATA *ird);
void send_flashcommand (FLASH_ENTRY *fentry,byte num,byte md);
word find_flashentry (byte data[],byte len,word hpnt,FLASH_ENTRY *fentry);
byte compare_code (byte data[],byte len,word adr,FLASH_ENTRY *fentry);
word get_hashcode (byte data[],byte len);
void read_flashdata (byte *pnt,word adr,word cnt);
void write_flashdata (byte *pnt,word adr,word cnt);
void set_flashadr (word adr);
void read_nextflashdata (byte *pnt,word cnt);
void signal_error (void);
void set_commanddata (int pos,IRDATA *irpnt,int bus,int tra);
void switch_relay (byte val);
byte irdb_findircommand (byte ircommand[],byte irlen,byte adr,byte *data);
byte irdb_send_string (byte *str,byte len);
byte IRDBSendBinary (byte *str,byte len);
byte irdb_send (byte remote[],byte command[],byte led,word mask,byte stat,byte pause);
void ADCReceive (IRDB_REMOTE_EX *rem,IRDB_COMMAND_COMPACT *com,IRRECEIVE *ir);
byte irdb_receive (void);
byte irdb_format_receive (byte ircommand[],byte len,byte start,byte cmp_len,word adr);
word udp_format_data (IRRECEIVE *ir,UDP_ASCII_RECEIVE *data,word pos,byte num,byte iradr);
void ReadIRDataFlash (word iadr,word tadr);
word _atoi (byte pnt[]);
byte irdb_findcommand (byte com[],IRDB_REMOTE_EX *irdb_rem,IRDB_COMMAND_COMPACT *irdb_com);
byte IRDBSendAction (IRDB_REMOTE_EX *rem,IRDB_COMMAND_COMPACT *irdb_com,IRRECEIVE *irr);
byte IRDBSendActionName (byte remote[],byte command[]);
void ProcessIRDBReceive (byte udp_mode,byte save_ird);
void irdb_relais (IRRECEIVE *ir);
int	 initIRDBPointer (void);

