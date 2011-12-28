// xekey.h
#ifndef _XEKEY_H
#define _XEKEY_H

// _XEKEYEX_INDEX
enum{
	XEKEYEX_VIDEO_DEVICE_PUBLIC_KEY = 0x100,
	XEKEYEX_VIDEO_DEVICE_PRIVATE_KEY = 0x101,
	XEKEYEX_VIDEO_DEVICE_CERTIFICATE = 0x102,
	XEKEYEX_IPTV_AV_PRIVATE_KEY = 0x103,
	XEKEYEX_IPTV_AUTH_PRIVATE_KEY = 0x104,
	XEKEYEX_IPTV_AV_CERTIFICATE = 0x105,
	XEKEYEX_IPTV_AUTH_CERTIFICATE = 0x106,
	XEKEYEX_IPTV_AV_SERIALIZED_CERTIFICATE = 0x107,
	XEKEYEX_IPTV_AUTH_SERIALIZED_CERTIFICATE = 0x108,
	XEKEYEX_VIDEO_DEVICE_PR_PUBLIC_KEY_SIGN = 0x109,
	XEKEYEX_VIDEO_DEVICE_PR_PRIVATE_KEY_SIGN = 0x10a,
	XEKEYEX_VIDEO_DEVICE_PR_PUBLIC_KEY_ENCRYPT = 0x10b,
	XEKEYEX_VIDEO_DEVICE_PR_PRIVATE_KEY_ENCRYPT = 0x10c,
	XEKEYEX_VIDEO_DEVICE_PR_CERTIFICATE = 0x10d,
	XEKEYEX_MAX_KEY_INDEX = 0x10e,
	
	XEKEYEX_IPTV_KEY_FIRST = 0x103,
	XEKEYEX_IPTV_KEY_LAST = 0x108,
	XEKEYEX_COUNT = 0xe,
};

//  _XEKEY_INDEX 
enum{
	XEKEY_MANUFACTURING_MODE = 0x0,
	XEKEY_ALTERNATE_KEY_VAULT = 0x1,
	XEKEY_RESTRICTED_PRIVILEGES_FLAGS = 0x2,
	XEKEY_RESERVED_BYTE3 = 0x3,
	XEKEY_ODD_FEATURES = 0x4,
	XEKEY_RESERVED_WORD2 = 0x5,
	XEKEY_RESTRICTED_HVEXT_LOADER = 0x6,
	XEKEY_POLICY_FLASH_SIZE = 0x7,
	XEKEY_POLICY_BUILTIN_USBMU_SIZE = 0x8,
	XEKEY_RESERVED_DWORD4 = 0x9,
	XEKEY_RESTRICTED_PRIVILEGES = 0xa,
	XEKEY_RESERVED_QWORD2 = 0xb,
	XEKEY_RESERVED_QWORD3 = 0xc,
	XEKEY_RESERVED_QWORD4 = 0xd,
	XEKEY_RESERVED_KEY1 = 0xe,
	XEKEY_RESERVED_KEY2 = 0xf,
	XEKEY_RESERVED_KEY3 = 0x10,
	XEKEY_RESERVED_KEY4 = 0x11,
	XEKEY_RESERVED_RANDOM_KEY1 = 0x12,
	XEKEY_RESERVED_RANDOM_KEY2 = 0x13,
	XEKEY_CONSOLE_SERIAL_NUMBER = 0x14,
	XEKEY_MOBO_SERIAL_NUMBER = 0x15,
	XEKEY_GAME_REGION = 0x16,
	XEKEY_CONSOLE_OBFUSCATION_KEY = 0x17,
	XEKEY_KEY_OBFUSCATION_KEY = 0x18,
	XEKEY_ROAMABLE_OBFUSCATION_KEY = 0x19,
	XEKEY_DVD_KEY = 0x1a,
	XEKEY_PRIMARY_ACTIVATION_KEY = 0x1b,
	XEKEY_SECONDARY_ACTIVATION_KEY = 0x1c,
	XEKEY_GLOBAL_DEVICE_2DES_KEY1 = 0x1d,
	XEKEY_GLOBAL_DEVICE_2DES_KEY2 = 0x1e,
	XEKEY_WIRELESS_CONTROLLER_MS_2DES_KEY1 = 0x1f,
	XEKEY_WIRELESS_CONTROLLER_MS_2DES_KEY2 = 0x20,
	XEKEY_WIRED_WEBCAM_MS_2DES_KEY1 = 0x21,
	XEKEY_WIRED_WEBCAM_MS_2DES_KEY2 = 0x22,
	XEKEY_WIRED_CONTROLLER_MS_2DES_KEY1 = 0x23,
	XEKEY_WIRED_CONTROLLER_MS_2DES_KEY2 = 0x24,
	XEKEY_MEMORY_UNIT_MS_2DES_KEY1 = 0x25,
	XEKEY_MEMORY_UNIT_MS_2DES_KEY2 = 0x26,
	XEKEY_OTHER_XSM3_DEVICE_MS_2DES_KEY1 = 0x27,
	XEKEY_OTHER_XSM3_DEVICE_MS_2DES_KEY2 = 0x28,
	XEKEY_WIRELESS_CONTROLLER_3P_2DES_KEY1 = 0x29,
	XEKEY_WIRELESS_CONTROLLER_3P_2DES_KEY2 = 0x2a,
	XEKEY_WIRED_WEBCAM_3P_2DES_KEY1 = 0x2b,
	XEKEY_WIRED_WEBCAM_3P_2DES_KEY2 = 0x2c,
	XEKEY_WIRED_CONTROLLER_3P_2DES_KEY1 = 0x2d,
	XEKEY_WIRED_CONTROLLER_3P_2DES_KEY2 = 0x2e,
	XEKEY_MEMORY_UNIT_3P_2DES_KEY1 = 0x2f,
	XEKEY_MEMORY_UNIT_3P_2DES_KEY2 = 0x30,
	XEKEY_OTHER_XSM3_DEVICE_3P_2DES_KEY1 = 0x31,
	XEKEY_OTHER_XSM3_DEVICE_3P_2DES_KEY2 = 0x32,
	XEKEY_CONSOLE_PRIVATE_KEY = 0x33,
	XEKEY_XEIKA_PRIVATE_KEY = 0x34,
	XEKEY_CARDEA_PRIVATE_KEY = 0x35,
	XEKEY_CONSOLE_CERTIFICATE = 0x36,
	XEKEY_XEIKA_CERTIFICATE = 0x37,
	XEKEY_CARDEA_CERTIFICATE = 0x38,
	XEKEY_MAX_KEY_INDEX = 0x39,
	
	// constant keys (in hv)
	XEKEY_CONSTANT_PIRS_KEY = 0x39,
	XEKEY_CONSTANT_ALT_MASTER_KEY = 0x3a,
	XEKEY_CONSTANT_ALT_LIVE_KEY = 0x3b,
	XEKEY_CONSTANT_MASTER_KEY = 0x3c,
	XEKEY_CONSTANT_LIVE_KEY = 0x3d,
	XEKEY_CONSTANT_XB1_GREEN_KEY = 0x3e,
	XEKEY_CONSTANT_SATA_DISK_SECURITY_KEY = 0x3f,
	XEKEY_CONSTANT_DEVICE_REVOCATION_KEY = 0x40,
	XEKEY_CONSTANT_XMACS_KEY = 0x41,
	XEKEY_CONSTANT_REVOCATION_LIST_NONCE = 0x42,
	XEKEY_CONSTANT_CROSS_PLATFORM_SYSLINK_KEY = 0x43,
	
	// special keys
	XEKEY_SPECIAL_KEY_VAULT_SIGNATURE = 0x44,
	XEKEY_SPECIAL_SECROM_DIGEST = 0x45,
	XEKEY_SPECIAL_SECDATA = 0x46,
	XEKEY_SPECIAL_DVD_FIRMWARE_KEY = 0x47,
	XEKEY_MAX_CONSTANT_INDEX = 0x48
};


#endif _XEKEY_H
