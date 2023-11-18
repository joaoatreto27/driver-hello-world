// Cabe�alhos necess�rios para o desenvolvimento de drivers no Windows.
#include <ntddk.h>
#include <wdf.h>

// Essas declara��es indicam a assinatura das fun��es
// A fun��o DriverEntry � o ponto de entrada do driver
DRIVER_INITIALIZE DriverEntry;
// KmdfHelloWorldEvtDeviceAdd � chamada quando um dispositivo � adicionado
EVT_WDF_DRIVER_DEVICE_ADD KmdfHelloWorldEvtDeviceAdd;

NTSTATUS
// Esta � a fun��o principal que � chamada quando o driver � carregado.
DriverEntry(
    // Representa o objeto do driver no kernel.
    _In_ PDRIVER_OBJECT     DriverObject,
    // Cont�m o caminho do registro associado ao driver.
    _In_ PUNICODE_STRING    RegistryPath
)
{
    // Vari�vel NTSTATUS para registrar sucesso ou falha
    NTSTATUS status = STATUS_SUCCESS;

    // Aloca o objeto de configura��o do driver
    WDF_DRIVER_CONFIG config;

    // Imprime "Hello World" para o DriverEntry
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: DriverEntry\n"));

    // Inicializa o objeto de configura��o do driver para registrar
    // o ponto de entrada para o retorno de chamada EvtDeviceAdd, KmdfHelloWorldEvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config,
        KmdfHelloWorldEvtDeviceAdd
    );

    // Cria o objeto do driver
    status = WdfDriverCreate(DriverObject,
        RegistryPath,
        WDF_NO_OBJECT_ATTRIBUTES,
        &config,
        WDF_NO_HANDLE
    );
    // Retorna o status da compila��o, sucesso no caso da compila��o ter sido conclu�da com sucesso
    return status;
}

NTSTATUS
// Fun��o chamada quando um dispositivo � adicionado
KmdfHelloWorldEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    // N�o estamos usando o objeto do driver,
    // ent�o precisamos marc�-lo como n�o referenciado
    UNREFERENCED_PARAMETER(Driver);

    NTSTATUS status;

    // Aloca o objeto do dispositivo
    WDFDEVICE hDevice;

    // Imprime "Hello World"
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: KmdfHelloWorldEvtDeviceAdd\n"));

    // Cria o objeto do dispositivo
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    // Retorna o status da compila��o, sucesso no caso da compila��o ter sido conclu�da com sucesso
    return status;
}
