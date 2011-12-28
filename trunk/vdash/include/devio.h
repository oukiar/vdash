// devio.h
#ifndef _DEVIO_H
#define _DEVIO_H

#include "kernel.h"
//NTSTATUS
//XxxDispatchRead(
//				IN PDEVICE_OBJECT  DeviceObject,
//				IN PIRP  Irp
//				);

// function location in array of u32's
enum {
	DEVICEOB_Start = 0,
	DEVICEOB_Del,
	DEVICEOB_Dismount,
	DEVICEOB_FCreate,
	DEVICEOB_FClose,
	DEVICEOB_FRead,
	DEVICEOB_FWrite,
	DEVICEOB_FQuery,
	DEVICEOB_FSet,
	DEVICEOB_FFlush,
	DEVICEOB_FQueryVol,
	DEVICEOB_FDirCntrl,
	DEVICEOB_FDevCntrl,
	DEVICEOB_FCleanup,
};

// INCOMPLETE!! DEVICE_TYPE
#define FILE_DEVICE_CD_ROM              0x00000002 // SataCdRomDriverObject
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003 // OdfxDriverObject
#define FILE_DEVICE_DISK                0x00000007 // SataDiskDriverObject
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008 // nomnil FatwDriverObject FatxDriverObject RawxDriverObject HfspDriverObject
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_MASS_STORAGE        0x0000002d // MassIoDriverObject
#define FILE_DEVICE_MASS1				0x0000003a // MassIoDriverObject
#define FILE_DEVICE_MASS2				0x0000003e // MassIoDriverObject
#define FILE_DEVICE_SFCX				0x0000003c // SfcxDriverObject
#define FILE_DEVICE_UNK1				0x0000003d
#define FILE_DEVICE_UNK2				0x00000040
#define FILE_DEVICE_UNK3				0x00000041 // SfcxMuDriverObject
#define FILE_DEVICE_UNK4				0x00000042
#define FILE_DEVICE_UNK5				0x00000043
#define FILE_DEVICE_MASS3				0x00000044 // MassIoDriverObject
#define FILE_DEVICE_MASS4				0x00000045 // MassIoDriverObject
#define FILE_DEVICE_UNK6				0x00000046
#define FILE_DEVICE_DEV_AUTH			0x00000047 // DevAuthIoDriverObject


// *********** PACKING STARTS HERE **************//
#pragma pack(push, 1)
// *********** PACKING STARTS HERE **************//


typedef struct _DISPATCHER_HEADER{
	unsigned char Type;
	unsigned char Absolute;
	unsigned char ProcessType;
	unsigned char Inserted;
	long SignalState;
	LIST_ENTRY WaitListHead;
} DISPATCHER_HEADER, *PDISPATCHER_HEADER; // 16

typedef struct _KEVENT{
	DISPATCHER_HEADER Header;
} KEVENT, *PKEVENT; // 16

typedef struct _KDEVICE_QUEUE{
	short Type;
	unsigned char Padding;
	unsigned char Busy;
	unsigned long Lock;
	LIST_ENTRY DeviceListHead;
} KDEVICE_QUEUE, *PKDEVICE_QUEUE; // 16

typedef struct _DRIVER_OBJECT{
	void  * DriverStartIo; // function pointers
	void  * DriverDeleteDevice;
	void  * DriverDismountVolume;
	void  * MajorFunction[0xB];
} DRIVER_OBJECT, *PDRIVER_OBJECT; //56

typedef struct _KDEVICE_QUEUE_ENTRY{
	LIST_ENTRY DeviceListEntry;
	unsigned long SortKey;
	unsigned char Inserted;
} KDEVICE_QUEUE_ENTRY, *PKDEVICE_QUEUE_ENTRY;

typedef struct _IO_COMPLETION_CONTEXT{
	void * Port;
	void * Key;
} IO_COMPLETION_CONTEXT, *PIO_COMPLETION_CONTEXT;

typedef struct _DEVICE_OBJECT{
	short Type;
	unsigned short Size;
	long ReferenceCount;
	PDRIVER_OBJECT DriverObject;
	void* MountedOrSelfDevice; //PDEVICE_OBJECT MountedOrSelfDevice;
	void * CurrentIrp;
	unsigned long Flags;
	void * DeviceExtension;
	unsigned char DeviceType;
	unsigned char StartIoFlags;
	char StackSize;
	unsigned char DeletePending;
	unsigned long SectorSize;
	unsigned long AlignmentRequirement;
	KDEVICE_QUEUE DeviceQueue;
	KEVENT DeviceLock;
	unsigned long StartIoCount;
	unsigned long StartIoKey;
} DEVICE_OBJECT, *PDEVICE_OBJECT;// 80

typedef struct _FILE_OBJECT{
	short Type;
	unsigned char Flags;
	unsigned char Flags2;
	PDEVICE_OBJECT DeviceObject;
	void * FsContext;
	void * FsContext2;
	long FinalStatus;
	LARGE_INTEGER CurrentByteOffset;
	void* RelatedFileObject; //PFILE_OBJECT RelatedFileObject;
	PIO_COMPLETION_CONTEXT CompletionContext;
	long LockCount;
	KEVENT Lock;
	KEVENT Event;
	LIST_ENTRY ProcessListEntry;
	LIST_ENTRY FileSystemListEntry;
	unsigned char IoPriority;
	unsigned char PoolPadding [0xF];
} FILE_OBJECT, *PFILE_OBJECT;

typedef void* KTHREAD; // THIS NEEDS MAJOR WORK!!

typedef struct _KAPC{
	short Type;
	unsigned char ApcMode;
	unsigned char Inserted;
	KTHREAD * Thread;
	LIST_ENTRY ApcListEntry;
	void * KernelRoutine; // function ptr
	void * RundownRoutine; // function ptr
	void * NormalRoutine; // function ptr
	void * NormalContext;
	void * SystemArgument1;
	void * SystemArgument2;
} KAPC, *PKAPC; // 40

typedef struct _IO_STACK_LOCATION{
	unsigned char MajorFunction;
	unsigned char MinorFunction;
	unsigned char Flags;
	unsigned char Control;
	union{
		struct {
			unsigned long DesiredAccess;
			unsigned long Options;
			unsigned short FileAttributes;
			unsigned short ShareAccess;
			PSTRING RemainingName;
		} Create;
		struct{
			unsigned long Length;
			union{
				unsigned long BufferOffset;
				void* CacheBuffer;
			};
			LARGE_INTEGER ByteOffset;
		} Read;
		struct{
			unsigned long Length;
			union{
				unsigned long BufferOffset;
				void* CacheBuffer;
			};
			LARGE_INTEGER ByteOffset;
		} Write;
		struct{
			unsigned long Length;
			PSTRING FileName;
		} QueryDirectory;
		struct{
			unsigned long Length;
			FILE_INFORMATION_CLASS FileInformationClass;
		} QueryFile;
		struct{
			unsigned long Length;
			FILE_INFORMATION_CLASS FileInformationClass;
			PFILE_OBJECT FileObject;
		} SetFile;
		struct{
			unsigned long Length;
			FSINFOCLASS FsInformationClass;
		} QueryVolume;
		struct{
			unsigned long Length;
			FSINFOCLASS FsInformationClass;
		} SetVolume;
		struct{
			unsigned long OutputBufferLength;
			void* InputBuffer;
			unsigned long InputBufferLength;
			unsigned long IoControlCode;
		} DeviceIoControl;
		struct{
			unsigned long Length;
			unsigned char* Buffer;
			unsigned long SectorNumber;
			unsigned long BufferOffset;
		} SectorIo;
		struct{
			void* Argument1;
			void* Argument2;
			void* Argument3;
			void* Argument4;
		} Others;
	} parameters; // parameters 16
	PDEVICE_OBJECT DeviceObject;
	PFILE_OBJECT FileObject;
	void* CompletionRoutine; // function long(*)()
	void* Context;
} IO_STACK_LOCATION, *PIO_STACK_LOCATION; // 36



// *********** PACKING ENDS HERE **************//
#pragma pack(pop)
// *********** PACKING ENDS HERE **************//



typedef struct _IRP{
	signed short Type;
	unsigned short Size;
	unsigned long Flags;
	LIST_ENTRY ThreadListEntry;
	IO_STATUS_BLOCK IoStatus;
	char StackCount;
	char CurrentLocation;
	unsigned char PendingReturned;
	unsigned char Cancel;
	void * UserBuffer;
	PIO_STATUS_BLOCK UserIosb;
	PKEVENT UserEvent;
	union{ // off 40
		struct{
			void * UserApcRoutine; // function void(*)()
			void * UserApcContext;
		} AsynchronousParameters;
		LARGE_INTEGER AllocationSize;
	} Overlay;
	union { // off 48
		struct {
			union{
				KDEVICE_QUEUE_ENTRY DeviceQueueEntry;
				LIST_ENTRY DeviceListEntry;
				void * DriverContext[0x4];
			};
			unsigned long LockedBufferLength;
			void* Thread; // PKTHREAD Thread;
			LIST_ENTRY ListEntry;
			union{
				PIO_STACK_LOCATION CurrentStackLocation;
				unsigned long PacketType;
			};
			PFILE_OBJECT OriginalFileObject;
		} Overlay;
		KAPC Apc;
		void * CompletionKey;
	} Tail;
	void * CancelRoutine; // function void(*)()
} IRP, *PIRP; // 96 - actually 92? appears the LARGE_INTEGER isn't packed here


//C_ASSERT(sizeof(KAPC) == 40);
//C_ASSERT(sizeof(IRP) == 96);
//C_ASSERT(sizeof(IO_STACK_LOCATION) == 36);
//C_ASSERT(sizeof(DRIVER_OBJECT) == 56);
//C_ASSERT(sizeof(DEVICE_OBJECT) == 80);
//C_ASSERT(sizeof(KDEVICE_QUEUE) == 16);
//C_ASSERT(sizeof(KEVENT) == 16);
//C_ASSERT(sizeof(DISPATCHER_HEADER) == 16);
 

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//	NTSTATUS IoCreateDevice(
//		__in      PDRIVER_OBJECT DriverObject,
//		__in      ULONG DeviceExtensionSize,
//		__in_opt  PUNICODE_STRING DeviceName,
//		__in      DWORD DeviceType, // DEVICE_TYPE
//		__in      ULONG DeviceCharacteristics,
//		__out     PDEVICE_OBJECT *DeviceObject
//		);
//
//#ifdef __cplusplus
//}
//#endif

#endif	//_DEVIO_H

