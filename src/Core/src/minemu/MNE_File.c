#include <minemu/MNE_Log.h>
#include <minemu/MNE_Flags.h>
#include <minemu/MNE_Memory.h>

long MNE_ReadFile(const char *filePath, const uint8_t flags, void (*callback)(const uint8_t *buffer,size_t bytesRead))
{
    long file_size = 0;
    uint8_t *buffer = NULL;
    size_t bytes_read = 0;

    FILE *file = fopen(filePath, "rb");
    if (file == NULL)
    {
        MNE_Log("Unable to open file %s\n", filePath);
        callback(NULL, 0);
    }

    // Get the size of the file
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    MNE_Log("Loaded file, %s: %li bytes\n", filePath, file_size);

    // Allocate a buffer for reading the file
    // buffer = (uint8_t *)calloc(1, file_size + 1);
    MNE_New(buffer, file_size + 1, uint8_t);

    bytes_read = fread(buffer, 1, file_size, file);

    // TODO: ADD DEBUG FLAG for dumping hex
    if (MNE_TEST_FLAG(flags, MNE_HEX_DUMP_FILE_FLAG))
    {
        MNE_HexDump(buffer, bytes_read);
    }

    callback(buffer, bytes_read);
    // Clean up resources
    free(buffer);
    fclose(file);
    return bytes_read;
}
