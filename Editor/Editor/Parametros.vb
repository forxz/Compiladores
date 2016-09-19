Imports System.IO

Public Class Parametros
    Dim rutaexe$ = ""
    Private Sub Parametros_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Try
            Dim freader As New StreamReader(Path.GetFullPath("param.txt"))
            Dim linea As String ', nombreparam As String, valorparam As String
            Dim datos As New ArrayList()
            
            linea = freader.ReadLine()
            If Not linea Is Nothing Then
                If linea.Length <> 0 Then
                    datos.Add(linea)
                    linea = linea.ToString.Split(";")(1)
                    Me.txtMaxLinea.Text = linea
                End If

            End If

            linea = freader.ReadLine()
            If Not linea Is Nothing Then
                If linea.Length <> 0 Then
                    datos.Add(linea)
                    linea = linea.ToString.Split(";")(1)
                    Me.txtMaxPal.Text = linea
                End If

            End If

            linea = freader.ReadLine()
            If Not linea Is Nothing Then
                If linea.Length <> 0 Then
                    datos.Add(linea)
                    linea = linea.ToString.Split(";")(1)
                    Me.txtMaxDigit.Text = linea
                End If

            End If

            linea = freader.ReadLine()
            If Not linea Is Nothing Then
                If linea.Length <> 0 Then
                    datos.Add(linea)
                    linea = linea.ToString.Split(";")(1)
                    Me.txtMaxID.Text = linea
                End If

            End If
            freader.Close()
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error de lectura", MessageBoxButtons.OK)
        End Try

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            Dim fwriter As New StreamWriter(Application.StartupPath & "\param.txt")
            Dim linea As String
            linea = "MAXLINEA;" & txtMaxLinea.Text
            fwriter.WriteLine(linea)
            linea = "MAXPAL;" & txtMaxPal.Text
            fwriter.WriteLine(linea)
            linea = "MAXDIGIT;" & txtMaxDigit.Text
            fwriter.WriteLine(linea)
            linea = "MAXID;" & txtMaxID.Text
            fwriter.WriteLine(linea)
            fwriter.Close()
            MessageBox.Show("Los parámetros se han actualizado correctamente", "", MessageBoxButtons.OK)
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error de escritura", MessageBoxButtons.OK)
        End Try
    End Sub
End Class