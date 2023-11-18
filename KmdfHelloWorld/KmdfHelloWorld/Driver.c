// Cabeçalhos necessários para o desenvolvimento de drivers no Windows.
#include <ntddk.h>
#include <wdf.h>

// Essas declarações indicam a assinatura das funções
// A função DriverEntry é o ponto de entrada do driver
DRIVER_INITIALIZE DriverEntry;
// KmdfHelloWorldEvtDeviceAdd é chamada quando um dispositivo é adicionado
EVT_WDF_DRIVER_DEVICE_ADD KmdfHelloWorldEvtDeviceAdd;

NTSTATUS
// Esta é a função principal que é chamada quando o driver é carregado.
DriverEntry(
    // Representa o objeto do driver no kernel.
    _In_ PDRIVER_OBJECT     DriverObject,
    // Contém o caminho do registro associado ao driver.
    _In_ PUNICODE_STRING    RegistryPath
)
{
    // Variável NTSTATUS para registrar sucesso ou falha
    NTSTATUS status = STATUS_SUCCESS;

    // Aloca o objeto de configuração do driver
    WDF_DRIVER_CONFIG config;

    // Imprime "Hello World" para o DriverEntry
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: DriverEntry\n"));

    // Inicializa o objeto de configuração do driver para registrar
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
    // Retorna o status da compilação, sucesso no caso da compilação ter sido concluída com sucesso
    return status;
}

NTSTATUS
// Função chamada quando um dispositivo é adicionado
KmdfHelloWorldEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    // Não estamos usando o objeto do driver,
    // então precisamos marcá-lo como não referenciado
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
    // Retorna o status da compilação, sucesso no caso da compilação ter sido concluída com sucesso
    return status;
}
