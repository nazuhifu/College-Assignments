/*
Fungsi untuk memilih file image yang akan dicompress
*/

package compressor;

import java.io.File;
import javax.swing.JFileChooser;

public class FileHandlerCompress {
    public File chooseFile() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File("."));
        int option = fileChooser.showOpenDialog(null);
        if (option == JFileChooser.APPROVE_OPTION) {
            return fileChooser.getSelectedFile();
        }
        return null;
    }
}
