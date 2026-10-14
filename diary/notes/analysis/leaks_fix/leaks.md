# Утечки 


При работе с приложением в процессе перехода между стейтами путём наблюдения за статусом приложения в диспетчере задач были обнаружены утечки памяти.


## Характеризация утечек

### Общие наблюдения

В процессе перехода между стейтами основной стейт-машины происходит аллокация и выделяется дополнительная память для данных текущего стейта.

Допустим, вместо 4мб стартового стейта программа начинает кушать 30мб на стейте главного меню.

Отсутствие полной деаллокации при обратном переходе между стейтами объясняется работой с указателями на объекты на стэке (указатели в области глобальной видимости в .cpp файле стейта).

Однако, существует проблема утечек, связанных с работой графического элемента My_SDL_button. "Играя" с запущенным приложением я обнаружил, что любое изменение графики элемента (а скорее всего, не всего элемента, а My_SDL_Textbox, вложенного в My_SDL_button композицией (вместо наследования)) приводит к дополнительному выделению памяти, которая навсегда остаётся занятой при дальнейшей работе с приложением - будь то прямое изменение цвета, размера всей кнопки (с учетом изменения текста) или изменение, через глобальные палитры цвета и шрифта (global_fonts.h и global_palette.h) при переходе между стейтами (вызывающем деструкторы всех объектов и приравнивание указателей к nullptr). 

"Игры" с обычным My_SDL_Textbox (не вложенным в кнопку композицией) характеризовались отсутствием обозначенных утечек памяти.


### Подозреваемые

Я подозреваю лишь класс My_SDL_button, особенно все места, где фигурируют изменения вложенного текстбокса (они были довольно хитро прописаны, чтобы не разрушать палитры шрифтов и не конфликтовать с базовым My_SDL_textbox (типо свои :reset_button_textbox_if_font_palette_switched() для текстбокса в кнопке и проч), соответственно, где-то могли быть ошибки логики приводящие к протекаемой аллокации чего-то связанного с SDL_ttf).

100% существуют ошибки в зоне обработки общего рескейла кнопки при нажатии на неё (хотя я и старался привести текстбокс при рескейле к последовательному выделению-удалению всех данных о текстбоксе, кроме первичных):

``` cpp

 // PRESS ANIMATION (simplified)
    
    // Cache
    if (this->button_clicked_tmp && this->press_offset == 0 && !this->po_cached)
    {
        int current_size = (int)this->button_textbox.get_font_size();
        
        if (current_size > 0) 
        {
            this->po_base_font = this->get_button_content_textbox()->ttf_font_link;
            this->po_base_size = current_size;
            this->po_cached = true;
        }
    }


    if (this->button_clicked_tmp)
    {
        if (this->push_mode_on && this->po_cached)
        {
            // Temporarily disable palette font management during press animation.
            // Previous textbox type will be restored on release.
            this->button_textbox.switch_textbox_type(NO_TYPE);


            if (this->press_offset < 5) this->press_offset++;
    
            int new_size = std::max(10, static_cast<int>(this->po_base_size - 0.5 * this->press_offset));
    
    
            // Only 4 + 1 (on release) TTF_OpenFont operation quantity control by:
            // (second condition for repetitive update block)
            if (this->press_offset <= 5 && this->button_textbox.get_font_size() != new_size)
            {
                TTF_Font* new_font = TTF_OpenFont(
                    this->button_textbox.get_font_path().c_str(),
                    new_size
                );
        
                if (new_font)
                {
                    // Close after 1 step in case when the font passed by the palette
                    // to use the basic font after end of the pressing - so we are not closing this->po_base_font
                    TTF_Font* current_font = this->get_button_content_textbox()->ttf_font_link;
                
                    if (current_font != nullptr && current_font != this->po_base_font) 
                    {
                        TTF_CloseFont(current_font);
                    }


                    // Set new font
                    this->button_textbox.set_ttf_font_link(new_font);
                    this->button_textbox.set_font_size(new_size);

                    this->get_button_content_textbox()->content_dirty = true;
                }
            }
        }
    }
    else
    {
        if (this->push_mode_on && this->press_offset >= 1)
        {
            this->button_textbox.switch_textbox_type(this->button_textbox.get_prev_textbox_type());

            
            // Clear the last font
            TTF_Font* font_to_destroy = this->get_button_content_textbox()->ttf_font_link;


            this->press_offset = 0;

            if (this->po_cached)
            {
                this->button_textbox.set_ttf_font_link(this->po_base_font);
                this->button_textbox.set_font_size(this->po_base_size);
                this->po_cached = false;
            }

            this->get_button_content_textbox()->content_dirty = true;

            
            if (font_to_destroy != nullptr && font_to_destroy != this->po_base_font)
            {
                TTF_CloseFont(font_to_destroy);
            }
        }
    }

```


+ Возможно где-то я неверно вызывал методы для базового My_SDL_textbox* вместо того чтобы прописать их нормально под композицию.


## Что надо

### Главное

Нужно найти причины утечек.

Составить понятный отчёт по причинам утечек в .md формате.

Придумать методику устранения утечек, не разрушающую текущую архитектуру проекта. Составить понятный гайдлайн по методике в .md формате (можно объединить с прошлым).

Предоставить файлы с готовым кодом, в котором утечки будут устранены на обзор


### Дополнительно:

Ответить, приводит ли глобальное определение указателей, даже как nullptr к выделению максимально возможно требуемой памяти на объект навсегда, как мне показалось, или причина в отсутствии возврата памяти на переходе между, допустим, Main_menu и Start с 30 мб обратно на 4мб кроется в чем-то другом. 

Составить в .md формате какую-то мини-лекцию, как вообще нормально выделиться, оставшись на той же архитектуре (можно всё в тот же файл).


### Важно:

Все требуемые материлы (новые версии файлов библиотек и требуемые .md) не внедрять в проект, а просто разместить в какой-то отдельной папке, допустим "diary/notes/analysis)