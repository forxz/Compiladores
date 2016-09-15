Public Class Form2

    'Private Sub Button3_Click(sender As Object, e As EventArgs)
    '    Dim i As Integer = Me.ListBox1.SelectedItems.Count
    '    For Each o As Object In Me.ListBox1.SelectedItems
    '        Me.ListBox2.Items.Add(o)
    '    Next
    '    While (i <> 0)
    '        i -= 1
    '        ListBox1.Items.Remove(ListBox1.SelectedItems(i))
    '    End While
    'End Sub

    'Private Sub Button4_Click(sender As Object, e As EventArgs)
    '    Dim i As Integer = Me.ListBox2.SelectedItems.Count
    '    For Each o As Object In Me.ListBox2.SelectedItems()
    '        Me.ListBox1.Items.Add(o)
    '    Next
    '    While (i <> 0)
    '        i -= 1
    '        ListBox2.Items.Remove(ListBox2.SelectedItems(i))
    '    End While
    'End Sub

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