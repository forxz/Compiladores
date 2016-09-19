Public Class Form2

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
        'Cargar resultados de archivo de texto del scanner, parser, etc cuando sea el momento

        'Carga el resultado del scanner
        If (System.IO.File.Exists("scannerResults.txt")) Then
            Try
                sReader = System.IO.File.OpenText("scannerResults.txt") 'Lee el archivo
                TokensRichTextBox.Text = sReader.ReadToEnd() 'Muestra el contenido del archivo en pantalla
                sReader.Close()
            Catch ex As Exception
                MessageBox.Show(ex.Message, "Error al leer archivo de Scanner", MessageBoxButtons.OK, MessageBoxIcon.Error)
            End Try
        End If


    End Sub
End Class