/**
 * ================================================================================
 * @file file_io.c
 * @author Dmitry Safonov (juvusoft@gmail.com)
 * @brief Definition of functions necessary for the work with file input-output.
 * @version 0.2
 * @date 2022-07-08
 * ================================================================================
 */

/* Standard library includes: */
#include <windows.h>
#include <assert.h>

/* Game engine includes: */
#include <file_io.h>
#include <utils.h>

File_t*
file_constructor(void)
{
    File_t *file;  /* Pointer to the File structure. */

    /* Memory allocation for the file object. */
    file = (File_t*)malloc(1 * sizeof(File_t));
    file->data = NULL;
    file->size = 0;
    return file;
}

void
file_destructor(File_t *file)
{
    /* Free memory allocated for the file data (using Win32API). */
    VirtualFree(file->data, 0, MEM_RELEASE);
    file->data = NULL;

    /* Free memory allocated for the file object. */ 
    free(file);
    file = NULL;
}

b32
file_load_to_memory(File_t *file, char *file_path)
{
    HANDLE file_handle;  /* Handle to the file on disc. */
    DWORD bytes_read;  /* Amount of bytes that was really read from the disc. */
    
    /* Create the file handle. */
    file_handle = CreateFileA(file_path, GENERIC_READ, FILE_SHARE_READ, 0, 
        OPEN_EXISTING, 0, 0);
    
    if (file_handle == INVALID_HANDLE_VALUE) 
    {
        /* Error with file handle creation (file not found). */
        return false;
    }

    /* Determine the file size. */
    file->size = (u64)GetFileSize(file_handle, 0);

    /* Memory allocation for the file data. */ 
    file->data = VirtualAlloc(0, file->size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    
    /* Read the file to the memory. */
    if ((ReadFile(file_handle, file->data, (DWORD)file->size, &bytes_read, 0))
        && (file->size == (u64)bytes_read))
    {
        /* Successful file reading. */
        return true;
    }
    else 
    {
        /* Error with reading file from the disc. */
        return false;
    }
}

b32
file_write_to_disc(File_t *file, char *file_path)
{
    /* TODO: Make definition of this method later on. */
   UNUSED(file);
   UNUSED(file_path);
   
   return true;
}
