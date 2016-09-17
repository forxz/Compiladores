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
End Class