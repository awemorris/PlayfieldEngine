import { common } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import testNapi from 'libentry.so';

const DOMAIN = 0x0000;

@Entry
@Component
struct Index {
  private xComponentId: string = 'suika_engine_view';
  private context = this.getUIContext().getHostContext() as common.UIAbilityContext;

  build() {
    Stack() {
      XComponent({
        id: this.xComponentId,
        type: 'surface',
        libraryname: 'entry'
      })
        .onLoad(() => {
          hilog.info(DOMAIN, 'XComponent', 'XComponent loaded!');
          testNapi.initResourceManager(this.context.resourceManager);
          testNapi.initFileDir(this.context.filesDir);
        })
        .onDestroy(() => {
          hilog.info(DOMAIN, 'XComponent', 'XComponent destroyed!');
        })
        .width('100%')
        .height('100%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Black)
  }
}