#include <minemu/MNE_Log.h>

void MNE_HexDump(uint8_t *buffer, const size_t size)
{
    // Print header
    MNE_Log("Loaded file hex dump:\n");
    MNE_Log("---------------------------------------------------------------\n");
    MNE_Log("Offset |                         Hexadecimal                   \n");
    MNE_Log("-------|-------------------------------------------------------\n");

    // Print buffer contents in hexadecimal format with ASCII representation
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i += 16)
    {
        // Check if the entire row is filled with zeros
        uint8_t allZeros = 1;
        for (j = i; j < i + 16 && j < size; j++)
        {
            if (buffer[j] != 0)
            {
                allZeros = 0;
                break;
            }
        }

        if (!allZeros)
        {
            // Print offset
            MNE_Log("%06X | ", i);

            // Print hexadecimal values
            for (j = i; j < i + 16 && j < size; j++)
            {
                MNE_Log("%02X ", buffer[j]);
            }
            MNE_Log("\n");
        }
    }

    // Print footer
    MNE_Log("-----------------------------------------------------------------\n");
}

