Public Class Form2
    Public rutaCodigoFuente As String
    Private Sub Button2_Click(sender As Object, e As EventArgs)
        If Me.TabControl1.SelectedIndex = Me.TabControl1.TabCount - 1 Then
            Me.TabControl1.SelectedIndex = 0
        Else
            Me.TabControl1.SelectedIndex = Me.TabControl1.SelectedIndex + 1
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs)
        If Me.TabControl1.SelectedIndex <> 0 Then
            Me.TabControl1.SelectedIndex = Me.TabControl1.SelectedIndex - 1
        Else
            Me.TabControl1.SelectedIndex = Me.TabControl1.TabCount - 1
        End If
    End Sub

    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim sReader As System.IO.StreamReader
        Dim p As New Process
        Dim salida As String

        p.StartInfo.UseShellExecute = False
        p.StartInfo.RedirectStandardOutput = True
        p.StartInfo.RedirectStandardError = True
        p.StartInfo.FileName = "scanner.exe"
        p.StartInfo.Arguments = Chr(34) + rutaCodigoFuente
        p.Start()
        'salida = p.StandardOutput.ReadToEnd        
        p.WaitForExit()
        'Cargar resultados de archivo de texto del scanner, parser, etc cuando sea el momento


        'Carga el resultado del scanner
        If (System.IO.File.Exists("resultado.txt")) Then
            Try
                sReader = System.IO.File.OpenText("resultado.txt") 'Lee el archivo
                TokensRichTextBox.Text = sReader.ReadToEnd() 'Muestra el contenido del archivo en pantalla
                sReader.Close()
            Catch ex As Exception
                MessageBox.Show(ex.Message, "Error al leer archivo de Scanner", MessageBoxButtons.OK, MessageBoxIcon.Error)
            End Try
        Else
            MessageBox.Show("No se encontro archivo resultado.txt", "Error al leer archivo de Scanner", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End If


    End Sub
End Class